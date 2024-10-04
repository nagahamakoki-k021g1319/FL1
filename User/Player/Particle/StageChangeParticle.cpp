#include "StageChangeParticle.h"
#include <imgui.h>
#include "GlobalVariables.h"

void StageChangeParticle::Initialize()
{
	stageChangeParticle_ = make_unique<ParticleManager>();
	stageChangeParticle_->Initialize();
	stageChangeParticle_->LoadTexture("particle.png");

	//指定した名前のグループを作る
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	globalVariables->CreateGroup(groupName_);
	//第一引数名のグループ内に第二引数名の調整項目が無ければ、第三引数を初期値として登録
	globalVariables->AddItem(groupName_, "randPos", 10.0f);
	globalVariables->AddItem(groupName_, "randVel", 0.4f);
	globalVariables->AddItem(groupName_, "randVelY", 0.0f);
	globalVariables->AddItem(groupName_, "startScale", 1.0f);
	globalVariables->AddItem(groupName_, "endScale", 0.1f);
	globalVariables->AddItem(groupName_, "liveTime", 30);
	globalVariables->AddItem(groupName_, "color", { 0.3f,1.0f,1.0f });
	globalVariables->AddItem(groupName_, "alpha", 0.7f);
	ApplyGlobalVariables();
}

void StageChangeParticle::Update()
{
	ApplyGlobalVariables();

	stageChangeParticle_->Update();
}

void StageChangeParticle::Draw()
{
	stageChangeParticle_->Draw();
}

void StageChangeParticle::ApplyGlobalVariables()
{
	//第一引数名のグループ内の第二引数名の調整項目の最新状態を読み込む
	randPos = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "randPos");
	randVel = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "randVel");
	randVelY = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "randVelY");
	startScale = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "startScale");
	endScale = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "endScale");
	liveTime = GlobalVariables::GetInstance()->GetIntValue(groupName_, "liveTime");
	color = GlobalVariables::GetInstance()->GetVector3Value(groupName_, "color");
	alpha = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "alpha");
}

void StageChangeParticle::EffSummary(Vector3 pos)
{
	//パーティクル範囲
	for (int i = 0; i < 20; i++) {
		//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		Vector3 posGas{};
		posGas.x += (float)rand() / RAND_MAX * randPos - randPos / 2.0f;
		posGas.y += (float)rand() / RAND_MAX * randPos - randPos / 2.0f;
		posGas.z += (float)rand() / RAND_MAX * randPos - randPos / 2.0f;
		posGas += pos;
		//速度
		Vector3 velGas{};
		//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
		velGas.x = (float)rand() / RAND_MAX * randVel - randVel / 2.0f;
		velGas.y = (float)rand() / RAND_MAX * randVelY - randVelY / 2.0f;
		velGas.z = (float)rand() / RAND_MAX * randVel - randVel / 0.2f;
		//重力に見立ててYのみ[-0.001f,0]でランダムに分布
		Vector3 accGas{};
		accGas.x = (float)rand() / RAND_MAX * rnd_accGas - rnd_accGas / 2.0f;
		accGas.y = (float)rand() / RAND_MAX * rnd_accGas - rnd_accGas / 2.0f;
		//追加
		stageChangeParticle_->Add(liveTime, posGas, velGas, accGas, startScale, endScale, { color.x,color.y,color.z,alpha });

	}
}
