/**
 * @file ImGuiManager.h
 * @brief ImGui管理
 */

#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"

// Imgui の管理
namespace MyEngine {
	class ImGuiManager {
	public:
		/**
		 * @brief 初期化
		*/
		void Initialize(WinApp* winApp, DirectXCommon* dxCommon);

		/**
		 * @brief 終了
		*/
		void Finalize();

		/**
		 * @brief Imgui受付開始
		*/
		void Begin();

		/**
		 * @brief Imgui受付終了
		*/
		void End();

		/**
		 * @brief 描画
		*/
		void Draw();


	private:
		DirectXCommon* dxCommon_;

		// SRV用デスクリプターヒープ
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_;

	public:



	};
}