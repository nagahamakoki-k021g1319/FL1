/**
 * @file Camera.cpp
 * @brief ゲームカメラ
 */

#include "Camera.h"

using namespace DirectX;
using namespace MyEngine;

Camera::Camera() {}

void Camera::Initialize(int window_width, int window_height){
	aspectRatio_ = (float)window_width / window_height;

	wtf.Initialize();

	isSyncRota = false;

	//ビュー行列の計算
	UpdateViewMatrix();

	// 射影行列の計算
	UpdateProjectionMatrix();

	// ビュープロジェクションの合成
	matViewProjection_ = matView_ * matProjection_;

	isShake_=false;
	shakeTimer_ = 0;
	shakeLimit_ = 10;
}

void Camera::Update() {
	//座標更新
	wtf.UpdateMat();

	UpdateViewMatrix();
	UpdateProjectionMatrix();
	matViewProjection_ = matView_ * matProjection_;
}

void Camera::UpdateViewMatrix() {

	// 視点座標
	Vector3 eyePosition = eye_ * wtf.matWorld + Shake();
	// 注視点座標
	Vector3 targetPosition = target_ * wtf.matWorld + Shake();
	// （仮の）上方向
	Vector3 upVector = up_;

	// カメラZ軸（視線方向）
	Vector3 cameraAxisZ = targetPosition - eyePosition;

	// 0ベクトルだと向きが定まらないので除外

	// ベクトルを正規化
	cameraAxisZ.nomalize();

	// カメラのX軸（右方向）
	Vector3 cameraAxisX;
	// X軸は上方向→Z軸の外積で求まる
	cameraAxisX = upVector.cross(cameraAxisZ);
	// ベクトルを正規化
	cameraAxisX.nomalize();

	// カメラのY軸（上方向）
	Vector3 cameraAxisY;
	// Y軸はZ軸→X軸の外積で求まる
	cameraAxisY = cameraAxisZ.cross(cameraAxisX);

	// ここまでで直交した3方向のベクトルが揃う
	//（ワールド座標系でのカメラの右方向、上方向、前方向）	

	// カメラ回転行列

	Matrix4 matCameraRot;
	// カメラ座標系→ワールド座標系の変換行列
	matCameraRot.m[0][0] = cameraAxisX.x;
	matCameraRot.m[0][1] = cameraAxisX.y;
	matCameraRot.m[0][2] = cameraAxisX.z;
	matCameraRot.m[0][3] = 0;
	matCameraRot.m[1][0] = cameraAxisY.x;
	matCameraRot.m[1][1] = cameraAxisY.y;
	matCameraRot.m[1][2] = cameraAxisY.z;
	matCameraRot.m[1][3] = 0;
	matCameraRot.m[2][0] = cameraAxisZ.x;
	matCameraRot.m[2][1] = cameraAxisZ.y;
	matCameraRot.m[2][2] = cameraAxisZ.z;
	matCameraRot.m[2][3] = 0;
	matCameraRot.m[3][0] = 0;
	matCameraRot.m[3][1] = 0;
	matCameraRot.m[3][2] = 0;
	matCameraRot.m[3][3] = 1;

	// 転置により逆行列（逆回転）を計算
	matView_ = ConvertXM::ConvertXMMATtoMat4(XMMatrixTranspose(ConvertXM::ConvertMat4toXMMAT(matCameraRot)));

	// 視点座標に-1を掛けた座標
	Vector3 reverseEyePosition = -eyePosition;
	// カメラの位置からワールド原点へのベクトル（カメラ座標系）
	float tX = cameraAxisX.dot(reverseEyePosition);	// X成分
	float tY = cameraAxisY.dot(reverseEyePosition);	// Y成分
	float tZ = cameraAxisZ.dot(reverseEyePosition);	// Z成分
	// 一つのベクトルにまとめる
	Vector3 translation = { tX,tY,tZ };
	// ビュー行列に平行移動成分を設定
	matView_.m[3][0] = translation.x;
	matView_.m[3][1] = translation.y;
	matView_.m[3][2] = translation.z;
	matView_.m[3][3] = 1;

#pragma region 全方向ビルボード行列の計算
	// ビルボード行列
	matBillboard_.m[0][0] = cameraAxisX.x;
	matBillboard_.m[0][1] = cameraAxisX.y;
	matBillboard_.m[0][2] = cameraAxisX.z;
	matBillboard_.m[0][3] = 0;
	matBillboard_.m[1][0] = cameraAxisY.x;
	matBillboard_.m[1][1] = cameraAxisY.y;
	matBillboard_.m[1][2] = cameraAxisY.z;
	matBillboard_.m[1][3] = 0;
	matBillboard_.m[2][0] = cameraAxisZ.x;
	matBillboard_.m[2][1] = cameraAxisZ.y;
	matBillboard_.m[2][2] = cameraAxisZ.z;
	matBillboard_.m[2][3] = 0;
	matBillboard_.m[3][0] = 0;
	matBillboard_.m[3][1] = 0;
	matBillboard_.m[3][2] = 0;
	matBillboard_.m[3][3] = 1;
#pragma region

#pragma region Y軸回りビルボード行列の計算
	// カメラX軸、Y軸、Z軸
	Vector3 ybillCameraAxisX, ybillCameraAxisY, ybillCameraAxisZ;

	// X軸は共通
	ybillCameraAxisX = cameraAxisX;
	// Y軸はワールド座標系のY軸
	ybillCameraAxisY = upVector.nomalize();
	// Z軸はX軸→Y軸の外積で求まる
	ybillCameraAxisZ = ybillCameraAxisX.cross(ybillCameraAxisY);

	// Y軸回りビルボード行列
	matBillboardY_.m[0][0] = cameraAxisX.x;
	matBillboardY_.m[0][1] = cameraAxisX.y;
	matBillboardY_.m[0][2] = cameraAxisX.z;
	matBillboardY_.m[0][3] = 0;
	matBillboardY_.m[1][0] = cameraAxisY.x;
	matBillboardY_.m[1][1] = cameraAxisY.y;
	matBillboardY_.m[1][2] = cameraAxisY.z;
	matBillboardY_.m[1][3] = 0;
	matBillboardY_.m[2][0] = cameraAxisZ.x;
	matBillboardY_.m[2][1] = cameraAxisZ.y;
	matBillboardY_.m[2][2] = cameraAxisZ.z;
	matBillboardY_.m[2][3] = 0;
	matBillboardY_.m[3][0] = 0;
	matBillboardY_.m[3][1] = 0;
	matBillboardY_.m[3][2] = 0;
	matBillboardY_.m[3][3] = 1;
#pragma endregion
}

void Camera::UpdateProjectionMatrix()
{
	// 透視投影による射影行列の生成
	matProjection_.MakePerspectiveL(
		FieldOfViewY(),
		aspectRatio_,
		0.1f, 100000.0f, matProjection_
	);
}

void Camera::MoveEyeVector(const Vector3& move)
{
	// 視点座標を移動し、反映
	Vector3 eye_moved = GetEye();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	SetEye(eye_moved);
}

void Camera::MoveVector(const Vector3& move)
{
	// 視点と注視点座標を移動し、反映
	Vector3 eye_moved = GetEye();
	Vector3 target_moved = GetTarget();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetEye(eye_moved);
	SetTarget(target_moved);
}

float Camera::FieldOfViewY() {
	return static_cast<float>(2 * atan(sensor_ / (2 * focalLengs_)));
}

Vector3 Camera::GetViewVec() {
	Vector3 viewVec = target_ - eye_;
	return viewVec.nomalize();
};

void Camera::StartShake() {
	if (isShake_ == false) {
		isShake_ = true;
		shakeTimer_ = 0;
	}
}

Vector3 Camera::Shake() {
	Vector3 shakeVec = { 0,0,0 };

	if (isShake_) {
		shakeTimer_++;
		if (shakeTimer_ < shakeLimit_) {
			float range = 0.1f;
			shakeVec.x = (float)rand() / RAND_MAX * range * 2.0f - range;
			shakeVec.y = (float)rand() / RAND_MAX * range * 2.0f - range;
			shakeVec* matProjection_;
		}
		else {
			isShake_ = false;
		}

	}

	return shakeVec;
}