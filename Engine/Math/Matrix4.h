/**
 * @file Matrix4.h
 * @brief Matrix4
 */

#pragma once
#include "Vector3.h"
//#include <DxLib.h>

namespace MyEngine {
	class Matrix4
	{
	public:

		float m[4][4];

	public:
		static Matrix4 Initialize();
		Matrix4();
		Matrix4(float num);
		/**
		 * @brief 成分を指定しての生成
		*/
		Matrix4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

		/**
		 * @brief 視線計算
		*/
		static void MakeOrthogonalL(float left, float right, float bottom, float top, float near_, float far_, Matrix4& matrix);
		/**
		 * @brief 視点計算
		*/
		static void MakeLookL(const Vector3& eye, const Vector3& target, const Vector3& up, Matrix4& mat);
		/**
		 * @brief 視点生成
		*/
		static void MakePerspectiveL(float fovAngleY, float aspect, float near_, float far_, Matrix4& matrix);
		/**
		 * @brief 見ている方向にベクトルを合わせる
		*/
		static Vector3 bVelocity(Vector3& velocity, Matrix4& mat);
		/**
		 * @brief 逆行列
		*/
		Matrix4 MakeInverse(const Matrix4* mat);
		/**
		 * @brief 初期化
		*/
		static Matrix4 MakeIdentity()
		{
			Matrix4 mat;
			return mat;
		}
		/**
		 * @brief 移動
		*/
		Vector3 transform(const Vector3& v, const Matrix4& matrix4);


		/**
		 * @brief 回転計算
		*/
		static Matrix4 Rotation(const Vector3& rotation, int X_1_Y_2_Z_3_XYZ_6);
	};
	// 代入演算子オーバーロード
	Matrix4& operator*=(Matrix4& m1, const Matrix4& m2);

	// 2項演算子オーバーロード
	const Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
	const Vector3 operator*(const Vector3& v, const Matrix4& m);
}