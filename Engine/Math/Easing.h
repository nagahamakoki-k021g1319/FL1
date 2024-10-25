/**
 * @file Easing.h
 * @brief イージング関数
 */

#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include <math.h>

namespace MyEngine {
	namespace Easing
	{
		/**
		 * @brief 線形補間
		*/
		float lerpFloat(const float start, const float end, const float time);
		/**
		 * @brief 二乗 float
		*/
		float InQuadFloat(const float start, const float end, const float time);
		float OutQuadFloat(const float start, const float end, const float time);
		float InOutQuadFloat(const float start, const float end, const float time);
		/**
		 * @brief 二乗 Vec2
		*/
		Vector2 InQuadVec2(const Vector2& start, const Vector2& end, const float time);
		Vector2 OutQuadVec2(const Vector2& start, const Vector2& end, const float time);
		Vector2 InOutQuadVec2(const Vector2& start, const Vector2& end, const float time);
		/**
		 * @brief 二乗 Vec3
		*/
		Vector3 InQuadVec3(const Vector3& start, const Vector3& end, const float time);
		Vector3 OutQuadVec3(const Vector3& start, const Vector3& end, const float time);
		Vector3 InOutQuadVec3(const Vector3& start, const Vector3& end, const float time);

		/**
		 * @brief 3乗 float
		*/
		float InCubicFloat(const float start, const float end, const float time);
		float OutCubicFloat(const float start, const float end, const float time);
		float InOutCubicFloat(const float start, const float end, const float time);
		/**
		 * @brief 3乗 Vec2
		*/
		Vector2 InCubicVec2(const Vector2& start, const Vector2& end, const float time);
		Vector2 OutCubicVec2(const Vector2& start, const Vector2& end, const float time);
		Vector2 InOutCubicVec2(const Vector2& start, const Vector2& end, const float time);
		/**
		 * @brief 3乗 Vec3
		*/
		Vector3 InCubicVec3(const Vector3& start, const Vector3& end, const float time);
		Vector3 OutCubicVec3(const Vector3& start, const Vector3& end, const float time);
		Vector3 InOutCubicVec3(const Vector3& start, const Vector3& end, const float time);

		/**
		 * @brief 4乗 float
		*/
		float InQuartFloat(const float start, const float end, const float time);
		float OutQuartFloat(const float start, const float end, const float time);
		float InOutQuartFloat(const float start, const float end, const float time);
		/**
		 * @brief 4乗 Vec2
		*/
		Vector2 InQuartVec2(const Vector2& start, const Vector2& end, const float time);
		Vector2 OutQuartVec2(const Vector2& start, const Vector2& end, const float time);
		Vector2 InOutQuartVec2(const Vector2& start, const Vector2& end, const float time);
		/**
		 * @brief 4乗 Vec3
		*/
		Vector3 InQuartVec3(const Vector3& start, const Vector3& end, const float time);
		Vector3 OutQuartVec3(const Vector3& start, const Vector3& end, const float time);
		Vector3 InOutQuartVec3(const Vector3& start, const Vector3& end, const float time);

		/**
		 * @brief 5乗 float
		*/
		float InQuintFloat(const float start, const float end, const float time);
		float OutQuintFloat(const float start, const float end, const float time);
		float InOutQuintFloat(const float start, const float end, const float time);
		/**
		 * @brief 5乗 Vec2
		*/
		Vector2 InQuintVec2(const Vector2& start, const Vector2& end, const float time);
		Vector2 OutQuintVec2(const Vector2& start, const Vector2& end, const float time);
		Vector2 InOutQuintVec2(const Vector2& start, const Vector2& end, const float time);
		/**
		 * @brief 5乗 Vec3
		*/
		Vector3 InQuintVec3(const Vector3& start, const Vector3& end, const float time);
		Vector3 OutQuintVec3(const Vector3& start, const Vector3& end, const float time);
		Vector3 InOutQuintVec3(const Vector3& start, const Vector3& end, const float time);
	} // namespace Easing
}