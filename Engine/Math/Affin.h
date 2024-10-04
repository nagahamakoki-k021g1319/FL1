/**
 * @file Affin.h
 * @brief アフィン行列
 */

#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "ConvertXM.h"

//#include "WorldTransform.h"

/// <summary>
/// アフィン行列 （角度指定：度数法）
/// </summary>
namespace MyEngine {
	namespace Affin {
		//円周率
		const float PI = 3.141592654f;

		/**
		 * @brief 度数法からラジアン変換
		*/
		float radConvert(float value);

		/**
		 * @brief ラジアンから度数法変換
		*/
		float degConvert(float value);

		/**
		 * @brief 単位行列設定
		*/
		Matrix4 matUnit();

		/**
		 * @brief ベクトルと行列の掛け算
		*/
		Vector3 VecMat(Vector3 vec, Matrix4 mat);

		/**
		 * @brief 平行移動
		*/
		Matrix4 matTrans(float moveX, float moveY, float moveZ);
		/**
		 * @brief 平行移動
		*/
		Matrix4 matTrans(Vector3 move);

		/**
		 * @brief x軸回転計算
		*/
		Matrix4 matRotateX(float rotationX);
		/**
		 * @brief y軸回転計算
		*/
		Matrix4 matRotateY(float rotationY);
		/**
		 * @brief z軸回転計算
		*/
		Matrix4 matRotateZ(float rotationZ);
		/**
		 * @brief 回転合成
		*/
		Matrix4 matRotation(float rotateX, float rotateY, float rotateZ);
		/**
		 * @brief 回転設定
		*/
		Matrix4 matRotation(Vector3 rotate);

		/**
		 * @brief サイズ設定
		*/
		Matrix4 matScale(float scaleX, float scaleY, float scaleZ);
		/**
		 * @brief サイズ変更
		*/
		Matrix4 matScale(Vector3 scale);

		/**
		 * @brief 行列計算
		*/
		Matrix4 matWorld(Vector3 move, Vector3 rotate, Vector3 scale);

		/**
		 * @brief ワールド座標取得
		*/
		Vector3 GetWorldTrans(Matrix4 matrix);

		/**
		 * @brief w除算
		*/
		Vector3 wDivision(Vector3 vector, Matrix4 matrix);

		/**
		 * @brief ベクトルと行列の掛け算
		*/
		Vector3 VecMat3D(Vector3 vec, Matrix4 mat);

		/**
		 * @brief sinとcosを計算
		*/
		void SinCos(float& sin_, float& cos_, float angle);

	} // namespace Affin
}