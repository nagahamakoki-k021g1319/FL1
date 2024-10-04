#include "FieldManager.h"
#include"BaseFieldObjectManager.h"
#include"GoalObject.h"
#include"NormalObstacleObject.h"
void FieldManager::Initialize()
{
	models.insert(std::make_pair("coin", MyEngine::Model::LoadFromOBJ("coin")));
	models.insert(std::make_pair("goal", MyEngine::Model::LoadFromOBJ("goal")));
	models.insert(std::make_pair("cone", MyEngine::Model::LoadFromOBJ("cone")));
	
}


void FieldManager::Load(const std::string& num)
{
	jsonLoader_.reset(LevelLoader::LoadJson(num));
	// レベルデータからオブジェクトを生成、配置
	for (auto& objectData : jsonLoader_->objects)
	{
		// ファイル名から登録済みモデルを検索
		Model* model = nullptr;
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end())
		{
			model = it->second.get();
		}
		//コイン
		if (objectData.fileName == "coin")
		{
			BaseFieldObjectManager::CreateCoinObject(model, objectData.translation, objectData.scaling);
		}
		//ゴール
		else if (objectData.fileName == "goal")
		{
			BaseFieldObjectManager::CreateGoalObject(model, objectData.translation, objectData.scaling,objectData.rotation);
			GoalObject::Reset();
		}
		else if(objectData.fileName=="cone")
		{
			BaseFieldObjectManager::CreateNormalObstacleObject(model, objectData.translation, objectData.scaling, Vector3(0.0f, 0.0f, 0.0f));
		}
	}
}
