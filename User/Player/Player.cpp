/**
 * @file Player.cpp
 * @brief プレイヤー本体
 */

#include"imgui.h"
#include"CollisionManager.h"
#include"Player.h"
#include"PlayerDash.h"
#include"PlayerJump.h"
#include"PlayerSlide.h"

using namespace Player;

Main::Main(){}
Main::~Main(){}

void Main::Initialize() {
	//モデル生成
	bodyModel_ = FbxLoader::GetInstance()->LoadModelFromFile("player");
	body_ = std::make_unique<FBXObject3d>();
	body_->Initialize();
	body_->SetModel(bodyModel_.get());
	body_->PlayAnimation(DASH, 3.0f);
	body_->Update();
	rocalWtf_.Initialize();
	isDraw_ = true;
	//ステート
	state_ = std::make_unique<Dash>();
	state_->Initialize();
	rotaMax_ = 3.141592f / 12.0f;
	moveMax_ = 6.0f;
	//当たり判定
	colliderRad_ = 0.7f;
	spine3BoneNum_ = bodyModel_->GetBoneNum("mixamorig:Spine3");
	spine2BoneNum_ = bodyModel_->GetBoneNum("mixamorig:Spine2");
	bodyCollider_ = new BaseCollider();
	bodyCollider_->SetAttribute(Attribute::PlyerBody);
	bodyCollider_->SetRad(colliderRad_);
	CollisionManager::GetInstance()->AddCollider(bodyCollider_);
	hitTimer_ = 0;
	hitTimerMax_ = 60;
	//パーティクル
	playerParticleManager_ = make_unique<PlayerParticleManager>();
	playerParticleManager_->Initialize();
	//影
	circleShadow_ = new CircleShadow();
	circleShadow_->SetActive(true);
	LightGroup::GetInstance()->SetCircleShadow(circleShadow_);
}

void Main::Update(const Transform& parentWTF) {
	parentWTF.matWorld;
	rocalWtf_.rotation = state_->GetRotaVector();
	rocalWtf_.position += state_->GetMoveVector();
	//幅に制限
	if (rocalWtf_.position.x > moveMax_) {
		rocalWtf_.position.x = moveMax_;
	}
	else if (rocalWtf_.position.x < -moveMax_) {
		rocalWtf_.position.x = -moveMax_;
	}

	circleShadow_->SetCasterPos(body_->wtf.position);

	rocalWtf_.UpdateMat();

	body_->wtf.position = rocalWtf_.position * parentWTF.matWorld;
	body_->wtf.rotation.y = rocalWtf_.rotation.y + parentWTF.rotation.y;
	
	//当たり判定
	bodyCollider_->SetCenter(body_->GetBonWorldPos(spine3BoneNum_));
	if (bodyCollider_->GetIsHit().normalObstacle == true) {
		hitTimer_++;
		if (hitTimer_ % 10 == 0) {
			if (isDraw_ == true) {
				isDraw_ = false;
			}else{
				isDraw_ = true;
			}
		}
		if (hitTimerMax_ < hitTimer_) {
			hitTimer_ = 0;
			isDraw_ = true;
			bodyCollider_->RemoveHit(Attribute::NormalObstacle);
		}
	}

	body_->Update();
	state_->Update(this);
	
	playerParticleManager_->ParticleCreate(PlayerParticleManager::BACKBOOST, body_->GetBonWorldPos(spine2BoneNum_));
	playerParticleManager_->Update();
}

void Main::FbxDraw() {
	if (isDraw_ == true) {
		body_->Draw();
	}
}

void Main::ParticleDraw() {
	playerParticleManager_->Draw();
}

void Main::TransitionTo(StateNum nextState) {
	if (nextState==StateNum::DASH_STATE) {
		state_ = std::make_unique<Dash>();
		AnimationChange(Main::Animation::DASH, 3.0f);
	}else if (nextState == StateNum::JUMP_STATE) {
		state_ = std::make_unique<Jump>();
	}else if (nextState == StateNum::SLIDE_STATE) {
		state_ = std::make_unique<Slide>();
		AnimationChange(Main::Animation::SLIDE);
	}
	state_->Initialize();
}