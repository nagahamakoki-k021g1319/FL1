/**
 * @file Framework.h
 * @brief エンジンフレームワーク
 */

#pragma once
#include"WinApp.h"
#include"DirectXCommon.h"
#include"FPS.h"
#include"Input.h"
#include"ImGuiManager.h"
#include"SpriteCommon.h"

namespace MyEngine {
	class Framework {
	public:
		virtual ~Framework() = default;
		Framework() = default;

		/**
		 * @brief 初期化
		*/
		virtual void Initialize();

		/**
		 * @brief 稼働
		*/
		void Run();

	protected:
		/**
		 * @brief 破棄
		*/
		virtual void Finalize();

		/**
		 * @brief 更新
		*/
		virtual void Update();

		/**
		 * @brief 描画
		*/
		virtual void Draw();

		/**
		 * @brief 終了フラグ
		*/
		virtual bool IsEndRequst();

	protected:
		WinApp* winApp_ = nullptr;
		DirectXCommon* dxCommon_ = nullptr;
		FPS* fps_ = new FPS;
		Input* input_ = nullptr;
		std::unique_ptr<ImGuiManager> imGui_;
	};
}