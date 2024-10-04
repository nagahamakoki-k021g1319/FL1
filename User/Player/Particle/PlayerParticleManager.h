#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "DirectXCommon.h"
#include "Matrix4.h"
#include "ParticleManager.h"
#include "Input.h"

#include"GameCamera.h"
#include "TGameCamera.h"
#include"CollisionManager.h"

#include "Smoke.h"
#include "BackBoost.h"
#include "Spark.h"
#include "StageChangeParticle.h"

using namespace MyEngine;
using namespace std;

class PlayerParticleManager
{
public :
	enum : uint32_t{
		SMOKE,
		BACKBOOST,
		SPARK,
		STAGECHANGE
	};
public:
	PlayerParticleManager();
	~PlayerParticleManager();

	void Initialize();

	void Update();

	void Draw();

	void ParticleCreate(uint32_t particleType,Vector3 createPos);

private:
	unique_ptr<Smoke> smoke_ = nullptr;
	unique_ptr<BackBoost> backBoost_ = nullptr;
	unique_ptr<Spark> spark_ = nullptr;
	unique_ptr<StageChangeParticle> stageChangeParticle_ = nullptr;

};

