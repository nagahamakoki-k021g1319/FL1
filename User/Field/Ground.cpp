#include "Ground.h"

Ground::Ground(Model* Model, Vector3 Pos, Vector3 Scale,TGameCamera*camera)
{
	shiftZ = Scale.z * 2.0f;
	scaleZ_ = Scale.z+5.0f;
	for (size_t i = 0; i < num; i++)
	{
		obj[i]=Object3d::Create();
		obj[i]->SetModel(Model);
		obj[i]->wtf.position = Pos;
		obj[i]->wtf.position.z += shiftZ * i;
		obj[i]->wtf.scale = Scale;
	}
	camera_ = camera;
}

void Ground::Update()
{
	for (size_t i = 0; i < num; i++)
	{
		if (camera_->wtf.position.z-scaleZ_>obj[i]->wtf.position.z)
		{
			obj[i]->wtf.position.z += shiftZ * num;
		}
		obj[i]->Update();
	}
}

void Ground::Draw()
{
	for (size_t i = 0; i < num; i++)
	{
		obj[i]->Draw();
	}
}
