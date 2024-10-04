/**
 * @file GameCamera.h
 * @brief ゲームカメラ
 */

#pragma once
#include"Camera.h"
#include "Vector2.h"
#include"Input.h"

namespace MyEngine {
	class GameCamera : public Camera {
	public:
		/**
		 * @brief 初期化
		*/
		GameCamera();
		void Initialize(int window_width, int window_height) override;

		/**
		 * @brief 更新
		*/
		void Update() override;

		/**
		 * @brief 感度変更
		*/
		static void ChangeSensitivity(Vector2 fluctuation);

		/**
		 * @brief 感度取得
		*/
		static Vector2 GetSensitivity() { return sensitivity_; };

		/**
		 * @brief 親座標セット
		*/
		void SetParentPos(Vector3 parentPos) { parentPos_ = parentPos; };
		/**
		 * @brief ロックオン座標セット
		*/
		void SetRockOnPos(Vector3 rockOnPos) { rockOnPos_ = rockOnPos; };

		/**
		 * @brief 親視線ベクトルセット
		*/
		void SetParentViewVec(Vector3 SetParentViewVec);


	private:
		/**
		 * @brief 回転
		*/
		void Rota();

		void ChangeRockOn();

		/**
		 * @brief 親の視線になる
		*/
		void ViewReset();

	private:
		Vector3 parentPos_;
		Vector3 localPos_;

		Vector3 rota_;
		float upLimit_;
		float downLimit_;

		static Vector2 sensitivity_;
		static Vector2 sensitivityMax_;
		static Vector2 sensitivityLimit_;

		Vector3 parentViewVec_;
		Vector3 resetVec;
		bool isViewReset;
		float resetSpeed;

		float rotaSpeedTimer_;
		float rotaSpeedMaxTime_;

		//ロックオン
		bool isRockOn_;
		Vector3 rockOnPos_;

	};
}