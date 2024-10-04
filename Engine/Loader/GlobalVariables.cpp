/**
 * @file  GlobalVariables.cpp
 * @brief  調整項目管理
 */
#include <windows.h>
#include"GlobalVariables.h"
#include"ImGui.h"
#include<fstream>

using namespace MyEngine;

GlobalVariables* GlobalVariables::GetInstance() {
	static GlobalVariables instance;
	return &instance;
}

void GlobalVariables::Update() {
	if (!ImGui::Begin("GlobalVariables", nullptr, ImGuiWindowFlags_MenuBar)) {
		ImGui::End();
		return;
	}

	for (std::map<std::string, Group>::iterator itGroup = datas_.begin(); itGroup != datas_.end(); ++itGroup) {
		const std::string& groupName = itGroup->first;
		Group& group = itGroup->second;

		if (!ImGui::BeginMenu(groupName.c_str()))
			continue;
		for (std::map<std::string, Item>::iterator itItem = group.items.begin(); itItem != group.items.end(); ++itItem) {
			const std::string& itemName = itItem->first;
			Item& item = itItem->second;
			//bool型
			if (holds_alternative<bool>(item.value)) {
				bool* ptr = get_if<bool>(&item.value);
				ImGui::Checkbox(itemName.c_str(), ptr);
			}
			//int32_t型
			if (holds_alternative<int32_t>(item.value)) {
				int32_t* ptr = get_if<int32_t>(&item.value);
				ImGui::InputInt(itemName.c_str(), ptr);
			}
			//float型
			else if (holds_alternative<float>(item.value)) {
				float* ptr = get_if<float>(&item.value);
				ImGui::InputFloat(itemName.c_str(), ptr);
			}
			//vector3型
			else if (holds_alternative<Vector3>(item.value)) {
				Vector3* ptr = get_if<Vector3>(&item.value);
				ImGui::InputFloat3(itemName.c_str(), reinterpret_cast<float*>(ptr));
			}
		}

		ImGui::Text("\n");
		if (ImGui::Button("Save")) {
			SaveFile(groupName);
			std::string message = format("{}.json saved.", groupName);
			MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
		}
		ImGui::EndMenu();
	}
	ImGui::End();
}

void GlobalVariables::LoadFiles() {
	std::filesystem::path dir(kDirectoryPath);
	//保存先ディレクトリ確認
	if (!std::filesystem::exists(kDirectoryPath)) {
		return;
	}

	//ディレクトリ内各ファイル処理
	std::filesystem::directory_iterator dir_it(dir);
	for (const std::filesystem::directory_entry& entry : dir_it) {
		//ファイルパス取得
		const std::filesystem::path& filePath = entry.path();
		//ファイル拡張子取得
		std::string extension = filePath.extension().string();
		//jsonファイル以外スキップ
		if (extension.compare(".json") != 0) {
			continue;
		}
		//ファイル読み込み
		LoadFile(filePath.stem().string());
	}
}

void GlobalVariables::LoadFile(const std::string& groupName) {
	std::string filePath = kDirectoryPath + groupName + ".json";
	std::ifstream ifs;
	//ファイル開く
	ifs.open(filePath);
	if (ifs.fail()) {
		assert(0);
	}
	//json文字列からjsonのデータ構造に展開
	json root;
	ifs >> root;
	//ファイルを閉じる
	ifs.close();
	//グループ検索
	json::iterator itGroup = root.find(groupName);
	//未登録チェック
	assert(itGroup != root.end());
	for (json::iterator itItem = itGroup->begin(); itItem != itGroup->end(); ++itItem) {
		//アイテム名取得
		const std::string& itemName = itItem.key();
		//bool型
		if (itItem->is_boolean()) {
			bool value = itItem->get<bool>();
			SetValue(groupName, itemName, static_cast<bool>(value));
		}
		//int32_t型
		else if (itItem->is_number_integer()) {
			int32_t value = itItem->get<int32_t>();
			SetValue(groupName, itemName, value);
		}
		//float型
		else if (itItem->is_number_float()) {
			double value = itItem->get<double>();
			SetValue(groupName, itemName, static_cast<float>(value));
		}
		//vector3型
		else if (itItem->is_array() && itItem->size() == 3) {
			Vector3 value = { itItem->at(0),itItem->at(1) ,itItem->at(2) };
			SetValue(groupName, itemName, value);
		}
	}
}

void GlobalVariables::SaveFile(const std::string& groupName) {
	//グループ検索
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);
	//未登録チェック
	assert(itGroup != datas_.end());
	
	json root;
	root = json::object();
	//jsonオブジェクトに登録
	root[groupName] = json::object();

	//各項目について
	for (std::map<std::string, Item>::iterator itItem = itGroup->second.items.begin(); itItem != itGroup->second.items.end(); ++itItem) {
		//項目名取得
		const std::string& itemName = itItem->first;
		//項目の参照取得
		Item& item = itItem->second;
		//bool型
		if (holds_alternative<bool>(item.value)) {
			root[groupName][itemName] = get<bool>(item.value);
		}
		//int32_t型
		else if (holds_alternative<int32_t>(item.value)) {
			root[groupName][itemName] = get<int32_t>(item.value);
		}
		//float型
		else if (holds_alternative<float>(item.value)) {
			root[groupName][itemName] = get<float>(item.value);
		}
		//vector3型
		if (holds_alternative<Vector3>(item.value)) {
			Vector3 value = get<Vector3>(item.value);
			root[groupName][itemName] = json::array({ value.x, value.y, value.z });
		}
	}

	//ディレクトリが無ければ作成
	std::filesystem::path dir(kDirectoryPath);
	if (!std::filesystem::exists(kDirectoryPath)) {
		std::filesystem::create_directory(kDirectoryPath);
	}
	//書き込むjsonファイルのフルパス合成
	std::string filePath = kDirectoryPath + groupName + ".json";
	//書き込み用ファイルストリーム
	std::ofstream ofs;
	ofs.open(filePath);
	if (ofs.fail()) {
		assert(0);
	}
	ofs << std::setw(4) << root << std::endl;
	ofs.close();
}

void GlobalVariables::CreateGroup(const std::string& groupNmae) {
	datas_[groupNmae];
}

void GlobalVariables::AddItem(const std::string& groupName, const std::string& key, bool value) {
	//グループ検索
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);
	std::map<std::string, Item>::iterator itItem = itGroup->second.items.find(key);
	//ないなら登録
	if (itItem == itGroup->second.items.end()) {
		SetValue(groupName, key, value);
	}
}

void GlobalVariables::AddItem(const std::string& groupName, const std::string& key, int32_t value) {
	//グループ検索
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);
	std::map<std::string, Item>::iterator itItem = itGroup->second.items.find(key);
	//ないなら登録
	if (itItem == itGroup->second.items.end()) {
		SetValue(groupName, key, value);
	}
}

void GlobalVariables::AddItem(const std::string& groupName, const std::string& key, float value) {
	//グループ検索
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);
	std::map<std::string, Item>::iterator itItem = itGroup->second.items.find(key);
	//ないなら登録
	if (itItem == itGroup->second.items.end()) {
		SetValue(groupName, key, value);
	}
}

void GlobalVariables::AddItem(const std::string& groupName, const std::string& key, const Vector3& value) {
	//グループ検索
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);
	std::map<std::string, Item>::iterator itItem = itGroup->second.items.find(key);
	//ないなら登録
	if (itItem == itGroup->second.items.end()) {
		SetValue(groupName, key, value);
	}
}

void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, bool value) {
	Group& group = datas_[groupName];
	Item newItem{};
	newItem.value = value;
	group.items[key] = newItem;
}

void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, int32_t value) {
	Group& group = datas_[groupName];
	Item newItem{};
	newItem.value = value;
	group.items[key] = newItem;
}

void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, float value) {
	Group& group = datas_[groupName];
	Item newItem{};
	newItem.value = value;
	group.items[key] = newItem;
}

void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, const Vector3& value) {
	Group& group = datas_[groupName];
	Item newItem{};
	newItem.value = value;
	group.items[key] = newItem;
}

bool GlobalVariables::GetBoolValue(const std::string& groupName, const std::string& key)const {
	const Group& group = datas_.at(groupName);
	const Item& item = group.items.at(key);
	return get<bool>(item.value);
}

int32_t GlobalVariables::GetIntValue(const std::string& groupName, const std::string& key)const {
	const Group& group = datas_.at(groupName);
	const Item& item = group.items.at(key);
	return get<int32_t>(item.value);
}

float GlobalVariables::GetFloatValue(const std::string& groupName, const std::string& key)const {
	const Group& group = datas_.at(groupName);
	const Item& item = group.items.at(key);
	return get<float>(item.value);
}

Vector3 GlobalVariables::GetVector3Value(const std::string& groupName, const std::string& key)const {
	const Group& group = datas_.at(groupName);
	const Item& item = group.items.at(key);
	return get<Vector3>(item.value);
}