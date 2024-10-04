/**
 * @file Camera.h
 * @brief カメラ
 */

#pragma once

#include "Vector3.h"
#include "Matrix4.h"
#include "Affin.h"
#include"Transform.h"
#include "ConvertXM.h"
#include"stdlib.h"

/// <summary>
/// カメラ基本機能
/// </summary>
namespace MyEngine {
	class Camera {
	public: // メンバ関数
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="window_width">画面幅</param>
		/// <param name="window_height">画面高さ</param>
		Camera();

		virtual void Initialize(int window_width, int window_height);

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~Camera() = default;

		/// <summary>
		/// 毎フレーム更新
		/// </summary>
		virtual void Update();

		/// <summary>
		/// ビュー行列を更新
		/// </summary>
		void UpdateViewMatrix();

		/// <summary>
		/// 射影行列を更新
		/// </summary>
		void UpdateProjectionMatrix();

		/// <summary>
		/// ビュー行列の取得
		/// </summary>
		/// <returns>ビュー行列</returns>
		inline const Matrix4& GetViewMatrix() { return matView_; };

		/// <summary>
		/// 射影行列の取得
		/// </summary>
		/// <returns>射影行列</returns>
		inline const Matrix4& GetProjectionMatrix() { return matProjection_; };

		/// <summary>
		/// ビュー射影行列の取得
		/// </summary>
		/// <returns>ビュー射影行列</returns>
		inline const Matrix4& GetViewProjectionMatrix() { return matViewProjection_; };

		/// <summary>
		/// ビルボード行列の取得
		/// </summary>
		/// <returns>ビルボード行列</returns>
		inline const Matrix4& GetBillboardMatrix() { return matBillboard_; };

		/// <summary>
		/// 視点座標の取得
		/// </summary>
		/// <returns>座標</returns>
		inline const Vector3& GetEye() { return eye_; };

		/// <summary>
		/// 視点座標の設定
		/// </summary>
		/// <param name="eye">座標</param>
		inline void SetEye(Vector3 eye) { this->eye_ = eye; viewDirty_ = true; };

		/// <summary>
		/// 注視点座標の取得
		/// </summary>
		/// <returns>座標</returns>
		inline const Vector3& GetTarget() { return target_; };

		/// <summary>
		/// 注視点座標の設定
		/// </summary>
		/// <param name="target">座標</param>
		inline void SetTarget(Vector3 target) { this->target_ = target; viewDirty_ = true; };

		/// <summary>
		/// 上方向ベクトルの取得
		/// </summary>
		/// <returns>上方向ベクトル</returns>
		inline const Vector3& GetUp() { return up_; };

		/// <summary>
		/// 上方向ベクトルの設定
		/// </summary>
		/// <param name="up">上方向ベクトル</param>
		inline void SetUp(Vector3 up) { this->up_ = up; viewDirty_ = true; };

		/// <summary>
		/// ベクトルによる視点移動
		/// </summary>
		/// <param name="move">移動量</param>
		void MoveEyeVector(const Vector3& move);

		/// <summary>
		/// ベクトルによる移動
		/// </summary>
		/// <param name="move">移動量</param>
		void MoveVector(const Vector3& move);

		float FieldOfViewY();

		Vector3 GetViewVec();

		/**
		 * @brief シェイク
		*/
		void StartShake();
		/**
		 * @brief シェイク
		*/
		Vector3 Shake();

		//親との回転同期
		bool isSyncRota;

		Transform wtf;

	protected: // メンバ変数
		// ビュー行列
		Matrix4 matView_ = ConvertXM::ConvertXMMATtoMat4(DirectX::XMMatrixIdentity());
		// ビルボード行列
		Matrix4 matBillboard_ = ConvertXM::ConvertXMMATtoMat4(DirectX::XMMatrixIdentity());
		// Y軸回りビルボード行列
		Matrix4 matBillboardY_ = ConvertXM::ConvertXMMATtoMat4(DirectX::XMMatrixIdentity());
		// 射影行列
		Matrix4 matProjection_ = ConvertXM::ConvertXMMATtoMat4(DirectX::XMMatrixIdentity());
		// ビュー射影行列
		Matrix4 matViewProjection_ = ConvertXM::ConvertXMMATtoMat4(DirectX::XMMatrixIdentity());
		// ビュー行列ダーティフラグ
		bool viewDirty_ = false;
		// 射影行列ダーティフラグ
		bool projectionDirty_ = false;
		// 視点座標
		Vector3 eye_ = { 0, 0, -1 };
		// 注視点座標
		Vector3 target_ = { 0, 0, 0 };
		// 上方向ベクトル
		Vector3 up_ = { 0, 1, 0 };
		// アスペクト比
		float aspectRatio_ = 1.0f;

		float distance_ = 6.0f;

		float focalLengs_ = 50;
		float sensor_ = 35;

		//カメラシェイク
		bool isShake_;
		int shakeTimer_;
		int shakeLimit_;
	};
}