#pragma once
#include <list>
#include <memory>
#include "Object3d.h"
#include"CollisionPrimitive.h"
#include"CollisionManager.h"

using namespace MyEngine;

class BaseFieldObject
{
public:
	bool isDelete = false;

	virtual ~BaseFieldObject() {}

	virtual void Update() = 0;
	virtual void Draw() = 0;

	
	std::unique_ptr<Object3d> object = nullptr;

	BaseCollider* sphere;

};



