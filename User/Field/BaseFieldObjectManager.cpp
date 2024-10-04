#include "BaseFieldObjectManager.h"
#include "CoinObject.h"
#include "GoalObject.h"
#include "NormalObstacleObject.h"

std::list<std::unique_ptr<BaseFieldObject>> BaseFieldObjectManager::manageBaseFieldObjectList;

void BaseFieldObjectManager::ManagerBaseFieldObject() {
	for (std::list<std::unique_ptr<BaseFieldObject>>::iterator itr = manageBaseFieldObjectList.begin(); itr != manageBaseFieldObjectList.end();) {
		BaseFieldObject* obj = (*itr).get();
		if (obj->isDelete) {
			itr = manageBaseFieldObjectList.erase(itr);
			continue;
		}

		obj->Update();
		obj->Draw();

		itr++;
	}
}

void BaseFieldObjectManager::Clear() {
	manageBaseFieldObjectList.clear();
}

void BaseFieldObjectManager::Init() {
	manageBaseFieldObjectList.clear();
}

BaseFieldObjectManager::BaseFieldObjectManager() {

}

BaseFieldObjectManager* BaseFieldObjectManager::GetInstance()
{
	static BaseFieldObjectManager instance;
	return &instance;
}

void BaseFieldObjectManager::CreateCoinObject(Model* Model, Vector3 Pos, Vector3 Scale)
{
	GetInstance()->manageBaseFieldObjectList.emplace_back(std::make_unique<CoinObject>(Model, Pos, Scale));
}

void BaseFieldObjectManager::CreateGoalObject(Model* Model, Vector3 Pos, Vector3 Scale, Vector3 Rotatin)
{
	GetInstance()->manageBaseFieldObjectList.emplace_back(std::make_unique<GoalObject>(Model, Pos, Scale, Rotatin));
}

void BaseFieldObjectManager::CreateNormalObstacleObject(Model* Model, Vector3 Pos, Vector3 Scale, Vector3 Rotatin)
{
	GetInstance()->manageBaseFieldObjectList.emplace_back(std::make_unique<NormalObstacleObject>(Model, Pos, Scale, Rotatin));
}
