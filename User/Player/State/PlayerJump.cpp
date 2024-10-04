/**
 * @file PlayerJump.cpp
 * @brief プレイヤーのジャンプパターン
 */
#include"Input.h"
#include"Easing.h"

#include"PlayerJump.h"
#include"Player.h"

using namespace Player;

Jump::Jump() {}

void Jump::Initialize() {
	GlobalVariables::GetInstance()->CreateGroup(groupName_);
	GlobalVariables::GetInstance()->AddItem(groupName_, "maxSpeed", 1.0f);
	GlobalVariables::GetInstance()->AddItem(groupName_, "rotaSpeed", 0.01f);
	GlobalVariables::GetInstance()->AddItem(groupName_, "maxHeight", 3.0f);
	GlobalVariables::GetInstance()->AddItem(groupName_, "reachTime", 25);
	moveVector_ = { 0,0,0 };
	timer_ = 0;
	ApplyGlobalVariables();
	if (Input::GetInstance()->PushKey(DIK_A)) {
		rotaVector_ += {0, -rotaSpeed_, 0};
	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		rotaVector_ += {0, rotaSpeed_, 0};
	}
}

void Jump::ApplyGlobalVariables() {
	maxSpeed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "maxSpeed");
	maxHeight_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "maxHeight");
	reachTime_ = GlobalVariables::GetInstance()->GetIntValue(groupName_, "reachTime");
	rotaSpeed_ = GlobalVariables::GetInstance()->GetFloatValue(groupName_, "rotaSpeed");
}

Jump::~Jump() {}

void Jump::Update(Main* player) {
	timer_++;
	Rota();
	Move(player->GetWorldTransform());
	StateTransition(player);
}

void Jump::Rota() {
	rotaVector_ = { 0,0,0 };
	if (Input::GetInstance()->PushKey(DIK_A)) {
		rotaVector_ += {0, -rotaSpeed_, 0};
	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		rotaVector_ += {0, rotaSpeed_, 0};
	}
}

void Jump::Move(Transform wtf) {
	float t = static_cast<float>(timer_) / static_cast<float>(reachTime_);
	float oltT = static_cast<float>(timer_-1) / static_cast<float>(reachTime_);
	float moveSpeed_ = MyEngine::Easing::OutQuad(0, maxHeight_, t) - MyEngine::Easing::OutQuad(0, maxHeight_, oltT);

	Vector3 result;
	result = { 0,moveSpeed_,maxSpeed_ };
	moveVector_ = Matrix4::bVelocity(result, wtf.matWorld);
	moveVector_.z = 0;
}

void Jump::StateTransition(Main* player) {
	if (timer_ > reachTime_ * 2) {
		player->AnimationChange(Main::Animation::DASH);
		player->TransitionTo(Main::StateNum::DASH_STATE);
	}
}