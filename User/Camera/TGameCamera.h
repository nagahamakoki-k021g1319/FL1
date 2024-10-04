#pragma once
#include "Camera.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"

class TGameCamera : public MyEngine::Camera {
public:
	enum CameraAngle {
		Back,
		RightBack,
		LeftBack,
	};

	enum SpeedLv {
		Low,
		Medium,
		High
	};

	/**
	 * @brief 初期化
	 */
	TGameCamera();
	void Initialize(int window_width, int window_height) override;

	/**
	 * @brief 更新
	 */
	void Update() override;

	void InputAngle();

	void AngleUpdate();

	void CameraUpdate();

	void DebugCameraUpdate();

	void SetParentTF(const MyEngine::Transform& parentWTF);

	void ApplyGlobalVariables();

	static TGameCamera* gameCamera_;

private:
	const char* groupName_ = "TGameCamera";
	MyEngine::Vector3 lowEyePos_;
	MyEngine::Vector3 lowTargetPos_;
	MyEngine::Vector3 mediumEyePos_;
	MyEngine::Vector3 mediumTargetPos_;
	MyEngine::Vector3 highEyePos_;
	MyEngine::Vector3 highTargetPos_;
	MyEngine::Vector3 lightEyePos_;
	MyEngine::Vector3 lightTargetPos_;
	MyEngine::Vector3 leftEyePos_;
	MyEngine::Vector3 leftTargetPos_;

	CameraAngle cameraAngle_ = Back;
	SpeedLv speedLv_ = Low;

	MyEngine::Vector3 cameraEye_;
	MyEngine::Vector3 cameraTarget_;

	bool isEase_ = false;
	float easeTimer_ = 0;
	float easeTime_ = 30;

	MyEngine::Vector3 endCameraEye_ = {0.0f, 4.0f, -9.0f};
	MyEngine::Vector3 endCameraTarget_ = {0.0f, 3.0f, 9.0f};
};
