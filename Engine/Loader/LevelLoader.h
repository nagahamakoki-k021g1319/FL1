/**
 * @file LevelLoader.h
 * @brief jsonファイルの読み込み
 */

#pragma once
#include<fstream>
#include <vector>
#include<Vector3.h>
#include<json.hpp>

#pragma warning( disable : 4324 )
using namespace MyEngine;

namespace MyEngine
{
// レベルデータ
struct LevelData {

	struct ObjectData  
	{
		// 平行移動
		Vector3 translation;
		// 回転角
		Vector3 rotation;
		// スケーリング
		Vector3 scaling;
		// ファイル名
		std::string fileName;
	};

	// オブジェクト配列
	std::vector<ObjectData> objects;

	std::vector < LevelData> *chidren;
};
	class LevelLoader
	{
	public:
		//jsonの読み込み
		static LevelData* LoadJson(const std::string& fileName_);

	private:
		//値を取得
		static LevelData* ImportValue(nlohmann::json& json_,LevelData* levelData_);
	};

}