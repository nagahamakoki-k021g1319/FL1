/**
 * @file DirectXCommon.h
 * @brief DirectX基盤
 */

#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"
//#include <DirectXTex.h>
#include <vector>


// Microsoft::WRL::を省略
//template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

//DirectX基盤
namespace MyEngine {
	class DirectXCommon {
	public://メンバ関数
		// Microsoft::WRL::を省略
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

		/**
		 * @brief 初期化
		*/
		void Initialize(WinApp* winApp);

		/**
		 * @brief デバイス初期化
		*/
		void InitializeDevice();

		/**
		 * @brief コマンドリスト初期化
		*/
		void InitializeCommand();

		/**
		 * @brief スワップチェーン初期化
		*/
		void InitializeSwapchain();

		/**
		 * @brief レンダーターゲットビュー初期化
		*/
		void InitializeRenderTargetView();

		/**
		 * @brief 深度バッファ初期化
		*/
		void InitializeDepthBuffer();

		/**
		 * @brief フェンスの初期化
		*/
		void InitializeFence();

		/**
		 * @brief 描画前処理
		*/
		void PreDraw();
		/**
		 * @brief 描画後処理
		*/
		void PostDraw();

		/**
		 * @brief デバイス取得
		*/
		ID3D12Device* GetDevice() const { return device.Get(); }

		/**
		 * @brief コマンドリスト取得
		*/
		ID3D12GraphicsCommandList* GetCommandList()const { return commandList.Get(); }

		/**
		 * @brief バックバッファの数を取得
		*/
		size_t GetBackBufferCount() const { return backBuffers.size(); }

	private:
		//DirectX12デバイス
		ComPtr<ID3D12Device> device;
		//DXGIファクトリ
		ComPtr<IDXGIFactory7> dxgiFactory;
		//バックバッファ
		std::vector<ComPtr<ID3D12Resource>> backBuffers;

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

		D3D12_RESOURCE_DESC depthResourceDesc{};

		//WindowsAPI
		WinApp* winApp_ = nullptr;

		HRESULT result;
		ComPtr<IDXGISwapChain4> swapChain;
		ComPtr<ID3D12CommandAllocator> cmdAllocator;
		ComPtr<ID3D12GraphicsCommandList> commandList;
		ComPtr<ID3D12CommandQueue> commandQueue;
		ComPtr<ID3D12DescriptorHeap> rtvHeap;
		ComPtr<ID3D12Fence> fence;
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
		ComPtr<ID3D12DescriptorHeap> dsvHeap;
		D3D12_RESOURCE_BARRIER barrierDesc{};
		UINT64 fenceVal = 0;
		ComPtr<ID3D12Resource> depthBuff;
	};
}