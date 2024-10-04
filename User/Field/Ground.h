#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Vector3.h"
#include<memory>
#include<array>
#include"TGameCamera.h"
using namespace MyEngine;

class Ground
{
public:
	Ground(Model* Model, Vector3 Pos, Vector3 Scale,TGameCamera*camera);

	void Update();

	void Draw();

private:
	static const int32_t num = 3;
	std::array< std::unique_ptr<Object3d>,num> obj;
	float shiftZ;
	float scaleZ_;
	TGameCamera* camera_;
};

