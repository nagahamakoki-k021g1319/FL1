#include "PlayerParticleManager.h"


PlayerParticleManager::PlayerParticleManager()
{
}

PlayerParticleManager::~PlayerParticleManager()
{
}

void PlayerParticleManager::Initialize()
{
	//スライディング
	smoke_ = make_unique<Smoke>();
	smoke_->Initialize();
	//後ろのブースト
	backBoost_ = make_unique<BackBoost>();
	backBoost_->Initialize();
	//火花
	spark_ = make_unique<Spark>();
	spark_->Initialize();
	//ステージ移動エフェクト
	stageChangeParticle_ = make_unique<StageChangeParticle>();
	stageChangeParticle_->Initialize();

}

void PlayerParticleManager::Update()
{
	smoke_->Update();
	backBoost_->Update();
	spark_->Update();
	stageChangeParticle_->Update();
}

void PlayerParticleManager::Draw()
{
	smoke_->Draw();
	backBoost_->Draw();
	/*spark_->Draw();*/
	/*stageChangeParticle_->Draw();*/

}

void PlayerParticleManager::ParticleCreate(uint32_t particleType, Vector3 createPos) 
{
	if (particleType == SMOKE) {
		smoke_->EffSummary(createPos);
	}else if (particleType == BACKBOOST) {
		backBoost_->EffSummary(createPos);
	}
	else if (particleType == SPARK){
		spark_->EffSummary(createPos);
	}
	else if (particleType == STAGECHANGE){
		stageChangeParticle_->EffSummary(createPos);
	}
}