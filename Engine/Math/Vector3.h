/**
 * @file Vector3.h
 * @brief 3次元ベクトル
 */

#pragma once
#include <DirectXMath.h>

namespace MyEngine {
	class Vector3 {
	public:
		float x;
		float y;
		float z;

	public:
		Vector3();
		Vector3(float x, float y, float z);

		/**
		 * @brief 長さを計算
		*/
		float length() const;

		/**
		 * @brief 正規化
		*/
		Vector3& nomalize();

		/**
		 * @brief 内積計算
		*/
		float dot(const Vector3& v) const;

		/**
		 * @brief 外積計算
		*/
		Vector3 cross(const Vector3& v) const;

		/**
		 * @brief ラープ関数
		*/
		static const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);

		/**
		 * @brief 2点間の距離
		*/
		static float Distance(const Vector3& start, const Vector3& end);

		/**
		 * @brief 2点間の角度
		*/
		static float Angle(const Vector3& start, const Vector3& end);

		/**
		 * @brief 0ベクトルにする
		*/
		static Vector3 Vector3Zero();

		/**
		 * @brief 2つが同じベクトルか
		*/
		static bool Vector3Equal(Vector3 v1, Vector3 v2);

		/**
		 * @brief 無限大かどうか
		*/
		bool Vector3IsInfinite();

		Vector3 operator+() const;
		Vector3 operator-() const;

		Vector3& operator+=(const Vector3& v);
		Vector3& operator-=(const Vector3& v);
		Vector3& operator*=(float s);
		Vector3& operator/=(float s);
	};

	const Vector3 operator+(const Vector3& v1, const Vector3& v2);
	const Vector3 operator-(const Vector3& v1, const Vector3& v2);
	const Vector3 operator*(const Vector3& v, float s);
	const Vector3 operator*(float s, const Vector3& v);
	const Vector3 operator/(const Vector3& v, float s);
	const bool operator==(const Vector3& v1, const Vector3& v2);
	const bool operator!=(const Vector3& v1, const Vector3& v2);
}