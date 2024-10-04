#include "TGameCamera.h"
#include "Player.h"
#include "Input.h"
#include "Easing.h"
#include <imgui.h>
#include "GlobalVariables.h"

using namespace MyEngine;
using namespace Player;

TGameCamera* TGameCamera::gameCamera_ = nullptr;

TGameCamera::TGameCamera() {}

void TGameCamera::Initialize(int window_width, int window_height) {
	Camera::Initialize(window_width, window_height);

	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	globalVariables->CreateGroup(groupName_);
	globalVariables->AddItem(groupName_, "lowEyePos_",       {0.0f, 4.0f, -9.0f});
	globalVariables->AddItem(groupName_, "lowTargetPos_",    {0.0f, 3.0f, 9.0f});
	globalVariables->AddItem(groupName_, "mediumEyePos_",    {0.0f, 8.0f, -12.0f});
	globalVariables->AddItem(groupName_, "mediumTargetPos_", {0.0f, 1.0f, 9.0f});
	globalVariables->AddItem(groupName_, "highEyePos_",      {0.0f, 10.0f, -18.0f});
	globalVariables->AddItem(groupName_, "highTargetPos_",   {0.0f, 1.0f, 9.0f});
	globalVariables->AddItem(groupName_, "lightEyePos_",     {5.0f, 6.0f, -15.0f});
	globalVariables->AddItem(groupName_, "lightTargetPos_",  {0.0f, 2.0f, 9.0f});
	globalVariables->AddItem(groupName_, "leftEyePos_",      {-5.0f, 6.0f, -15.0f});
	globalVariables->AddItem(groupName_, "leftTargetPos_",   {0.0f, 2.0f, 9.0f});
	globalVariables->AddItem(groupName_, "cameraAngle", Back);
	globalVariables->AddItem(groupName_, "speedLv", Low);
	ApplyGlobalVariables();
}

void TGameCamera::ApplyGlobalVariables() {
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	lowEyePos_		 = globalVariables->GetVector3Value(groupName_, "lowEyePos_");
	lowTargetPos_	 = globalVariables->GetVector3Value(groupName_, "lowTargetPos_");
	mediumEyePos_	 = globalVariables->GetVector3Value(groupName_, "mediumEyePos_");
	mediumTargetPos_ = globalVariables->GetVector3Value(groupName_, "mediumTargetPos_");
	highEyePos_		 = globalVariables->GetVector3Value(groupName_, "highEyePos_");
	highTargetPos_	 = globalVariables->GetVector3Value(groupName_, "highTargetPos_");
	lightEyePos_	 = globalVariables->GetVector3Value(groupName_, "lightEyePos_");
	lightTargetPos_  = globalVariables->GetVector3Value(groupName_, "lightTargetPos_");
	leftEyePos_		 = globalVariables->GetVector3Value(groupName_, "leftEyePos_");
	leftTargetPos_	 = globalVariables->GetVector3Value(groupName_, "leftTargetPos_");
	cameraAngle_ = (CameraAngle)globalVariables->GetIntValue(groupName_, "cameraAngle");
	speedLv_ = (SpeedLv)globalVariables->GetIntValue(groupName_, "speedLv");
}

void TGameCamera::Update() {
	ApplyGlobalVariables();
	if (isEase_) {
		easeTimer_++;

		if (easeTimer_ >= easeTime_) {
			isEase_ = false;
			easeTimer_ = 0;
		}
	} 
	else {
		/*InputAngle();

		AngleUpdate();*/
	}

	Camera::Update();
}

void TGameCamera::InputAngle() {
	if (Input::GetInstance()->TriggerKey(DIK_DOWNARROW)) {
		cameraAngle_ = Back;
		isEase_ = true;
	}

	if (Input::GetInstance()->TriggerKey(DIK_RIGHTARROW)) {
		cameraAngle_ = RightBack;
		isEase_ = true;
	}

	if (Input::GetInstance()->TriggerKey(DIK_LEFTARROW)) {
		cameraAngle_ = LeftBack;
		isEase_ = true;
	}
}

void TGameCamera::AngleUpdate() {
	switch (cameraAngle_) {
	case TGameCamera::Back:
		if (Input::GetInstance()->TriggerKey(DIK_1)) {
			speedLv_ = Low;
			isEase_ = true;
		}

		if (Input::GetInstance()->TriggerKey(DIK_2)) {
			speedLv_ = Medium;
			isEase_ = true;
		}

		if (Input::GetInstance()->TriggerKey(DIK_3)) {
			speedLv_ = High;
			isEase_ = true;
		}
		break;
	case TGameCamera::RightBack:
		break;
	case TGameCamera::LeftBack:
		break;
	default:
		break;
	}
}

void TGameCamera::CameraUpdate() {
	if (isEase_) {
		switch (cameraAngle_) {
		case TGameCamera::Back:
			switch (speedLv_) {
			case TGameCamera::Low:
				endCameraEye_ = lowEyePos_;
				endCameraTarget_ = lowTargetPos_;
				cameraEye_ = MyEngine::Easing::OutQuadVec3(
				    cameraEye_, endCameraEye_, easeTimer_ / easeTime_);
				cameraTarget_ = MyEngine::Easing::OutQuadVec3(
				    cameraTarget_, endCameraTarget_, easeTimer_ / easeTime_);
				break;
			case TGameCamera::Medium:
				endCameraEye_ = mediumEyePos_;
				endCameraTarget_ = mediumTargetPos_;
				cameraEye_ = MyEngine::Easing::OutQuadVec3(
				    cameraEye_, endCameraEye_, easeTimer_ / easeTime_);
				cameraTarget_ = MyEngine::Easing::OutQuadVec3(
				    cameraTarget_, endCameraTarget_, easeTimer_ / easeTime_);
				break;
			case TGameCamera::High:
				endCameraEye_ = highEyePos_;
				endCameraTarget_ = highTargetPos_;
				cameraEye_ = MyEngine::Easing::OutQuadVec3(
				    cameraEye_, endCameraEye_, easeTimer_ / easeTime_);
				cameraTarget_ = MyEngine::Easing::OutQuadVec3(
				    cameraTarget_, endCameraTarget_, easeTimer_ / easeTime_);
				break;
			default:
				break;
			}
			break;
		case TGameCamera::RightBack:
			endCameraEye_ = lightEyePos_;
			endCameraTarget_ = lightTargetPos_;
			cameraEye_ =
			    MyEngine::Easing::OutQuadVec3(cameraEye_, endCameraEye_, easeTimer_ / easeTime_);
			cameraTarget_ = MyEngine::Easing::OutQuadVec3(
			    cameraTarget_, endCameraTarget_, easeTimer_ / easeTime_);
			break;
		case TGameCamera::LeftBack:
			endCameraEye_ = leftEyePos_;
			endCameraTarget_ = leftTargetPos_;
			cameraEye_ =
			    MyEngine::Easing::OutQuadVec3(cameraEye_, endCameraEye_, easeTimer_ / easeTime_);
			cameraTarget_ = MyEngine::Easing::OutQuadVec3(
			    cameraTarget_, endCameraTarget_, easeTimer_ / easeTime_);
			break;
		default:
			break;
		}

		eye_ = cameraEye_;
		target_ = cameraTarget_;
	} else {
		cameraEye_ = endCameraEye_;
		cameraTarget_ = endCameraTarget_;

		eye_ = cameraEye_;
		target_ = cameraTarget_;
	}
}

void TGameCamera::DebugCameraUpdate() {
	switch (cameraAngle_) {
	case TGameCamera::Back:
		switch (speedLv_) {
		case TGameCamera::Low:
			endCameraEye_ = lowEyePos_;
			endCameraTarget_ = lowTargetPos_;
			break;
		case TGameCamera::Medium:
			endCameraEye_ = mediumEyePos_;
			endCameraTarget_ = mediumTargetPos_;
			break;
		case TGameCamera::High:
			endCameraEye_ = highEyePos_;
			endCameraTarget_ = highTargetPos_;
			break;
		default:
			break;
		}
		break;
	case TGameCamera::RightBack:
		endCameraEye_ = lightEyePos_;
		endCameraTarget_ = lightTargetPos_;
		break;
	case TGameCamera::LeftBack:
		endCameraEye_ = leftEyePos_;
		endCameraTarget_ = leftTargetPos_;
		break;
	default:
		break;
	}

	cameraEye_ = endCameraEye_;
	cameraTarget_ = endCameraTarget_;

	eye_ = cameraEye_;
	target_ = cameraTarget_;
}

void TGameCamera::SetParentTF(const Transform& parentWTF) { 
	wtf = parentWTF;
}
