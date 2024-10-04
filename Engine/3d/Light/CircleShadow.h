/**
 * @file CircleShadow.h
 * @brief 丸影
 */

#pragma once
#include"Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace MyEngine {
	class CircleShadow {
	public:
		inline void SetDir(const Vector4& dir) { dir_ = dir.Normalization(); }
		inline void SetCasterPos(const Vector3 casterPos) { casterPos_ = casterPos; }
		inline void SetDistanceCasterLight(float distanceCasterLight) { distanceCasterLight_ = distanceCasterLight; }
		inline void SetAtten(const Vector3& atten) { atten_ = atten; }
		inline void SetFactorAngle(const Vector2& factorAngle) {
			factorAngleCos_.x = cosf(factorAngle.x);
			factorAngleCos_.y = cosf(factorAngle.y);
		}
		inline void SetActive(bool active) { active_ = active; }

		inline const Vector4& GetDir() { return dir_; }
		inline const Vector3& GetCasterPos() { return casterPos_; }
		inline float GetDistanceCasterLight() { return distanceCasterLight_; }
		inline const Vector3& GetAtten() { return atten_; }
		inline const Vector2 GetFactorAngleCos() { return factorAngleCos_; }
		inline bool IsActive() { return active_; }
	public:
		//定数バッファ用データ構造体
		struct ConstBufferData{
			Vector4 dir;
			Vector3 casterPos;
			float distanceCasterLight;
			Vector3 atten;
			float pad3;
			Vector2 factorAngleCos;
			int active;
			float pad4;
		};
	private:
		Vector4 dir_ = { 0,-1,0,0 };
		float distanceCasterLight_ = 1.0f;
		Vector3 casterPos_ = { 0,0,0 };
		Vector3 atten_ = { 0.0f, 0.2f, 0.0f };
		Vector2 factorAngleCos_ = { 0.9f,1.0f };
		int active_ = false;
	};
}