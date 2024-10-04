/**
 * @file Transform.h
 * @brief 3次元座標データ
 */

#pragma once
#include "Matrix4.h"
#include "Affin.h"

namespace MyEngine {
	class Transform
	{
	public:
		Transform();
		~Transform();
		/**
		 * @brief 初期化
		*/
		void Initialize();

		/**
		 * @brief Matrix4更新
		*/
		void UpdateMat();
	public:
		// ローカルスケール
		Vector3 scale = { 1,1,1 };
		// X,Y,Z軸回りのローカル回転角
		Vector3 rotation = { 0,0,0 };
		// ローカル座標
		Vector3 position = { 0,0,0 };
		// ローカルワールド変換行列
		Matrix4 matWorld = Affin::matUnit();

	};
}