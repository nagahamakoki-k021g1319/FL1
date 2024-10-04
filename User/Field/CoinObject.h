#pragma once
#include "BaseFieldObject.h"
#include "Model.h"
#include "Vector3.h"
using namespace MyEngine;


class CoinObject: public BaseFieldObject
{
public:
	
	CoinObject(Model* Model, Vector3 Pos, Vector3 Scale);

	~CoinObject()
	{
		//当たり判定をマネージャから解除
		CollisionManager::GetInstance()->RemoveCollider(sphere);
		delete sphere;
		LightGroup::GetInstance()->RemoveCircleShadow(circleShadow_);
	}

	void Update() override;

	void Draw() override;

	//影
	CircleShadow* circleShadow_;
};

