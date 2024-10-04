/**
 * @file GameCamera.cpp
 * @brief ゲームカメラ
 */

#include"GameCamera.h"
#include<cmath>

using namespace MyEngine;

Vector2 GameCamera::sensitivity_ = { 0.05f,0.05f };
Vector2 GameCamera::sensitivityMax_ = { 0.1f,0.1f };
Vector2 GameCamera::sensitivityLimit_ = { 0.02f,0.02f };

GameCamera::GameCamera() {}

void GameCamera::Initialize(int window_width, int window_height) {
	Camera::Initialize(window_width, window_height);

	parentPos_ = { 0,0,0 };
	localPos_ = { 0,3.5f,0 };
	distance_ = 6.0f;

	const float PI = 3.141592f;
	rota_ = { 0.0f,PI,0.f };
	upLimit_ = PI / 5.0f;
	downLimit_ = -PI / 3.0f;
	
	isViewReset = false;
	resetSpeed = 0.2f;

	rotaSpeedTimer_ = 0;
	rotaSpeedMaxTime_ = 30;

	//ロックオン
	isRockOn_ = false;
	rockOnPos_ = { 0,0,0 };
}

void GameCamera::Update() {
	ChangeRockOn();
	Rota();
	ViewReset();

	UpdateViewMatrix();
	UpdateProjectionMatrix();
	matViewProjection_ = matView_ * matProjection_;
}

void GameCamera::Rota() {
	if (isRockOn_ == true) {
		target_ = parentPos_ + localPos_;
		Vector3 vec = rockOnPos_ - target_;
		eye_ = target_ + (-vec.nomalize() * distance_);
		rota_.y = atan2f(-vec.x, -vec.z);
	}else{
		Vector2 stick = Input::GetInstance()->GetRightStickVec();
		if (stick.x != 0 || stick.y != 0) {
			if (rotaSpeedTimer_ < rotaSpeedMaxTime_) {
				rotaSpeedTimer_++;
			}
		}
		else {
			rotaSpeedTimer_ = 0;
		}
		Vector2 velocity = { stick.x * sensitivity_.x ,stick.y * sensitivity_.y };
		velocity *= static_cast<float>(std::lerp(0, 1, rotaSpeedTimer_ / rotaSpeedMaxTime_));
		rota_.x += velocity.y;
		rota_.y += velocity.x;
		if (rota_.x > upLimit_) {
			rota_.x = upLimit_;
		}
		else if (rota_.x < downLimit_) {
			rota_.x = downLimit_;
		}

		Matrix4 cameraRot = Matrix4::Rotation(rota_, 6);

		target_ = parentPos_ + localPos_;

		Vector3 forward = { 0,0,distance_ };
		forward = Matrix4::bVelocity(forward, cameraRot);
		forward.nomalize();

		eye_ = target_ + (forward * distance_);
	}
}

void GameCamera::ViewReset() {
	if (Input::GetInstance()->PButtonTrigger(X)) {
		rota_ = parentViewVec_;
	}



	//Vector3 viewDifference = parentViewVec_ - rota_;
	//resetVec = viewDifference.nomalize();
	//if (isViewReset) {
	//	rota_ += resetSpeed * resetVec;
	//	if (resetSpeed > abs(parentViewVec_.y - rota_.y)) {
	//		rota_ = parentViewVec_;
	//		isViewReset = false;
	//	}

	//}else if (Input::GetInstance()->PButtonTrigger(X)) {
	//	isViewReset = true;
	//}


}

void GameCamera::SetParentViewVec(Vector3 SetParentViewVec) {
	parentViewVec_ = SetParentViewVec;
	const float PI = 3.141592f;
	parentViewVec_.y += PI;
};

void GameCamera::ChangeSensitivity(Vector2 fluctuation) {
	sensitivity_ += fluctuation;

	if (sensitivity_.x < sensitivityLimit_.x) {
		sensitivity_.x = sensitivityLimit_.x;
	}else if (sensitivity_.x > sensitivityMax_.x) {
		sensitivity_.x = sensitivityMax_.x;
	}

	if (sensitivity_.y < sensitivityLimit_.y) {
		sensitivity_.y = sensitivityLimit_.y;
	}
	else if (sensitivity_.y > sensitivityMax_.y) {
		sensitivity_.y = sensitivityMax_.y;
	}
}

void GameCamera::ChangeRockOn() {
	if (Input::GetInstance()->PButtonTrigger(RSTICK)) {
		if (isRockOn_) {
			isRockOn_ = false;
		}else {
			isRockOn_ = true;
		}
	}
}