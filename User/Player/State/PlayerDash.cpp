/**
 * @file PlayerDash.cpp
 * @brief プレイヤーの走りパターン
 */
#include"Input.h"

#include"PlayerDash.h"
#include"Player.h"

using namespace Player;

Dash::Dash() {}

void Dash::Initialize() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "maxSpeed", 1.0f);
	GlobalVariables::GetInstance()->AddItem(groupName_, "rotaSpeed", 0.01f);
	moveVector_ = { 0,0,0 };
	ApplyGlobalVariables();
	if (Input::GetInstance()->PushKey(DIK_A)) {
		rotaVector_ += {0, -rotaSpeed_, 0};
	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		rotaVector_ += {0, rotaSpeed_, 0};
	}
}

void Dash::ApplyGlobalVariables() {
	maxSpeed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "maxSpeed");
	rotaSpeed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "rotaSpeed");
}

Dash::~Dash() {}

void Dash::Update(Main* player) {
	Rota();
	Move(player->GetWorldTransform());
	StateTransition(player);
}

void Dash::Rota() {
	rotaVector_ = { 0,0,0 };
	if (Input::GetInstance()->PushKey(DIK_A)) {
		rotaVector_ += {0, -rotaSpeed_, 0};
	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		rotaVector_ += {0, rotaSpeed_, 0};
	}
}

void Dash::Move(Transform wtf) {
	Vector3 result;
	result = { 0,0,maxSpeed_ };
	moveVector_ = Matrix4::bVelocity(result,wtf.matWorld);
	moveVector_.z = 0;
}

void Dash::StateTransition(Main* player) {
	if (Input::GetInstance()->TriggerKey(DIK_S)) {
		player->AnimationChange(Main::Animation::STAND);
		player->TransitionTo(Main::StateNum::SLIDE_STATE);
	}
	else if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		player->AnimationChange(Main::Animation::JUMP);
		player->TransitionTo(Main::StateNum::JUMP_STATE);
	}
}