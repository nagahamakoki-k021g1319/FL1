/**
 * @file ObjLoader.cpp
 * @brief スプライト読み込み
 */
#include"ObjLoader.h"
#include<fstream>
#include<json.hpp>

ObjLoader* ObjLoader::GetInstance() {
	static ObjLoader instance;
	return &instance;
}

void ObjLoader::LoadAllModel() {
	std::filesystem::path dir(kDirectoryPath);
	//ディレクトリ内各ファイル走査
	std::filesystem::directory_iterator dir_it(dir);
	for (const std::filesystem::directory_entry& entry : dir_it) {
		//各ファイル処理
		std::filesystem::directory_iterator model_dir_it(entry);
		for (const std::filesystem::directory_entry& mode_entry : model_dir_it) {
			//ファイルパス取得
			const std::filesystem::path& filePath = mode_entry.path();
			//ファイル拡張子取得
			std::string extension = filePath.extension().string();
			//jsonファイル以外スキップ
			if (extension.compare(".obj") != 0) {
				continue;
			}
			//objモデル読み込み
			LoadModel(filePath.stem().string());
			break;
		}
	}
}

void ObjLoader::LoadModel(const std::string& modelName) {
	items_[modelName] = std::move(Model::LoadFromOBJ(modelName));
}

Model* ObjLoader::GetModel(const std::string& modelName) {
	return items_.at(modelName).get();
}