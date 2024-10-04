#pragma once
#include "BaseFieldObject.h"
class GoalObject : public BaseFieldObject
{
public:

	GoalObject(Model* Model, Vector3 Pos, Vector3 Scale, Vector3 Rotation);

	~GoalObject()
	{
		//当たり判定をマネージャから解除
		CollisionManager::GetInstance()->RemoveCollider(sphere);
		delete sphere;
	}

	void Update() override;

	void Draw() override;

	static bool GetGoaled()
	{
		return goaled_flag;
	}

	static void Reset()
	{
		goaled_flag = false;
	}


private:
	static bool goaled_flag;
};

