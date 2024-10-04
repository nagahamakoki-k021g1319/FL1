/**
 * @file GlobalVariables.h
 * @brief 調整項目管理
 */
#pragma once
#include<variant>
#include<map>
#include<string>
#include"Vector3.h"
#include<json.hpp>

using json = nlohmann::json;

namespace MyEngine {
	class GlobalVariables {
	public:
		/**
		 * @brief インスタンス取得
		*/
		static GlobalVariables* GetInstance();
		/**
		 * @brief 更新
		*/
		void Update();
		/**
		 * @brief 全ファイル読み込み
		*/
		void LoadFiles();
		/**
		 * @brief グループ作成
		*/
		void CreateGroup(const std::string& groupNmae);
		/**
		 * @brief int値取得
		*/
		bool GetBoolValue(const std::string& groupName, const std::string& key)const;
		/**
		 * @brief int値取得
		*/
		int32_t GetIntValue(const std::string& groupName, const std::string& key)const;
		/**
		 * @brief float値取得
		*/
		float GetFloatValue(const std::string& groupName, const std::string& key)const;
		/**
		 * @brief vector3値取得
		*/
		Vector3 GetVector3Value(const std::string& groupName, const std::string& key)const;
		/**
		 * @brief 項目追加(bool)
		*/
		void AddItem(const std::string& groupName, const std::string& key, bool value);
		/**
		 * @brief 項目追加(int)
		*/
		void AddItem(const std::string& groupName, const std::string& key, int32_t value);
		/**
		 * @brief 項目追加(float)
		*/
		void AddItem(const std::string& groupName, const std::string& key, float value);
		/**
		 * @brief 項目追加(Vector3)
		*/
		void AddItem(const std::string& groupName, const std::string& key, const Vector3& value);
	private:
		/**
		 * @brief ファイル読み込み
		*/
		void LoadFile(const std::string& groupName);
		/**
		 * @brief ファイル書き出し
		*/
		void SaveFile(const std::string& groupName);
		/**
		 * @brief 値セット(bool)
		*/
		void SetValue(const std::string& groupName, const std::string& key, bool value);
		/**
		 * @brief 値セット(int)
		*/
		void SetValue(const std::string& groupName, const std::string& key, int32_t value);
		/**
		 * @brief 値セット(float)
		*/
		void SetValue(const std::string& groupName, const std::string& key, float value);
		/**
		 * @brief 値セット(Vector3)
		*/
		void SetValue(const std::string& groupName, const std::string& key, const Vector3& value);
	private:
		//項目
		struct Item {
			std::variant<bool, int32_t, float, Vector3> value;
		};
		//グループ
		struct Group {
			std::map<std::string, Item> items;
		};

	private:
		//保存先ファイルパス
		const std::string kDirectoryPath = "Resources/GlobalVariables/";
		std::map<std::string, Group> datas_;
	};
}