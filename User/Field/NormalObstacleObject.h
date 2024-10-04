#pragma once
#include "BaseFieldObject.h"
class NormalObstacleObject : public BaseFieldObject
{
public:

	NormalObstacleObject(Model* Model, Vector3 Pos, Vector3 Scale, Vector3 Rotation);

	~NormalObstacleObject()
	{
		//当たり判定をマネージャから解除
		CollisionManager::GetInstance()->RemoveCollider(sphere);
		delete sphere;
	}

	void Update() override;

	void Draw() override;

private:

	int animationTimer = 0;
	const int animationTime = 60;

	bool animated = false;
	int downScore_ = 3;
};

