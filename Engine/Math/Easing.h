/**
 * @file Easing.h
 * @brief イージング関数
 */

#pragma once
#include "Vector3.h"
#include <math.h>

namespace MyEngine {
	class Easing {
	public:
		/**
		 * @brief float型easeInQuad
		*/
		static float InQuad(const float& start, const float& end, const float time);
		/**
		 * @brief float型easeOutQuad
		*/
		static float OutQuad(const float& start, const float& end, const float time);
		/**
		 * @brief float型easeInOutQuad
		*/
		static float InOutQuad(const float& start, const float& end, const float time);

		/**
		 * @brief Vector3型easeInQuadベクター
		*/
		static Vector3 InQuadVec3(const Vector3& start, const Vector3& end, const float time);
		/**
		 * @brief Vector3型easeOutQuad
		*/
		static Vector3 OutQuadVec3(const Vector3& start, const Vector3& end, const float time);
		/**
		 * @brief Vector3型easeInOutQuad
		*/
		static Vector3 InOutQuadVec3(const Vector3& start, const Vector3& end, const float time);
	};
}