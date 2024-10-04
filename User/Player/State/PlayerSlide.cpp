/**
 * @file PlayerSlide.cpp
 * @brief プレイヤーのスライドパターン
 */
#include"Input.h"

#include"PlayerSlide.h"
#include"Player.h"

using namespace Player;

Slide::Slide() {}

void Slide::Initialize() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "maxSpeed", 1.0f);
	GlobalVariables::GetInstance()->AddItem(groupName_, "limit", 30);
	timer_ = 0;
	moveVector_ = { 0,0,0 };
	ApplyGlobalVariables();
}

void Slide::ApplyGlobalVariables() {
	maxSpeed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "maxSpeed");
	limit_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "limit");
}

Slide::~Slide() {}

void Slide::Update(Main* player) {
	timer_++;
	player->CreateParticle(PlayerParticleManager::SMOKE, player->GetWorldTransform().position);
	Rota();
	Move(player->GetWorldTransform());
	StateTransition(player);
}

void Slide::Rota() {
	rotaVector_ = { 0,0,0 };
}

void Slide::Move(Transform wtf) {
	Vector3 result;
	result = { 0,0,maxSpeed_ };
	moveVector_ = Matrix4::bVelocity(result, wtf.matWorld);
	moveVector_.z = 0;
}

void Slide::StateTransition(Main* player) {
	if (timer_ > limit_) {
		player->AnimationChange(Main::Animation::DASH,3.0f);
		player->TransitionTo(Main::StateNum::DASH_STATE);
	}
}