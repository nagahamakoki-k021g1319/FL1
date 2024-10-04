#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "DirectXCommon.h"
#include "Matrix4.h"
#include "ParticleManager.h"
#include "Input.h"

using namespace MyEngine;
using namespace std;

class Spark
{
private:


public:

	void Initialize();

	void Update();

	void Draw();

	void ApplyGlobalVariables();

	void EffSummary(Vector3 pos);

private:
	unique_ptr<ParticleManager> sparkParticle_;
	int backBoostEffTimer_ = 0;
	bool isBackBoostEffFlag_ = false;

	const float rnd_posGas = 0.0f;
	const float rnd_velGasz = 0.02f;
	const float rnd_accGas = 0.000001f;

	//グループ名、jsonファイル名になる
	const char* groupName_ = "sparkParticle";
	//調整項目例
	float randPos;
	float randVel;
	float randVelY;
	float startScale;
	float endScale;
	int liveTime;
	Vector3 color;
	float alpha;
};

