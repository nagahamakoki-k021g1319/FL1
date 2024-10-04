#pragma once
#include "ParticleManager.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "DirectXCommon.h"

struct ParticleSetting
{
	MyEngine::Vector3 pos;
	MyEngine::Vector3 vel;
	float acc;
	int life;
	MyEngine::Vector2 scale;
	MyEngine::Vector4 color;
	int num;
};

class PlayerBasicParticle
{
private:

	ParticleSetting setting;
	std::unique_ptr<MyEngine::ParticleManager> particle;

public:

	void Initialize(const std::string& fileName,const ParticleSetting& set);

	void Add(const MyEngine::Vector3& pos);

	void Update();

	void Draw();

	

	PlayerBasicParticle() = default;
	~PlayerBasicParticle() = default;
};

