/**
 * @file FbxModel.h
 * @brief FBX本体
 */

#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <string>

#include <DirectXMath.h>
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Affin.h"

#include "FbxLoader.h"
#include "FBXModel.h"

#include "LightGroup.h"
#include "Camera.h"
#include "Transform.h"

namespace MyEngine {
	class FBXObject3d
	{
	protected: // エイリアス
		// Microsoft::WRL::を省略
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
		// DirectX::を省略
		using XMFLOAT2 = DirectX::XMFLOAT2;
		using XMFLOAT3 = DirectX::XMFLOAT3;
		using XMFLOAT4 = DirectX::XMFLOAT4;
		using XMMATRIX = DirectX::XMMATRIX;

	public:
		// 定数バッファ用データ構造体
		struct ConstBufferDataB0{
			Matrix4 viewProj;
			Matrix4 world;
			Vector3 cameraPos;
			Vector4 color;
		};

		//ボーンの最大数
		static const int MAX_BONES = 128;

		//定数バッファ用のデータ構造体(スキニング)
		struct ConstBufferDataSkin
		{
			XMMATRIX bones[MAX_BONES];
		};


	public: // 静的メンバ関数
		/// <summary>
		/// グラフィックパイプラインの生成
		/// </summary>
		static void CreateGraphicsPipeline();

		/// <summary>
		/// グラフィックパイプラインの生成
		/// </summary>
		// setter
		static void SetDevice(ID3D12Device* device) { FBXObject3d::device_ = device; }
		/**
		 * @brief カメラ設定
		*/
		static void SetCamera(Camera* camera) { FBXObject3d::camera_ = camera; }
		/**
		 * @brief 描画前処理
		*/
		static void PreDraw(ID3D12GraphicsCommandList* cmdList);
		/**
		 * @brief 描画後処理
		*/
		static void PostDraw();

		static void SetLight(LightGroup* lightGroup) { lightGroup_ = lightGroup; }

	private: // 静的メンバ変数
		// デバイス
		static ID3D12Device* device_;
		// カメラ
		static Camera* camera_;

		static LightGroup* lightGroup_;
		// ルートシグネチャ
		static ComPtr<ID3D12RootSignature> rootsignature;
		// パイプラインステートオブジェクト
		static ComPtr<ID3D12PipelineState> pipelinestate;
		// コマンドリスト
		static ComPtr<ID3D12GraphicsCommandList> cmdList_;


	public: // メンバ関数
		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 毎フレーム処理
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		void SetModel(FBXModel* fbxmodel) { this->fbxmodel_ = fbxmodel; }

		/// <summary>
		/// アニメーション開始
		/// </summary>
		void PlayAnimation(int animationNum = 0, float speed = 1.0f, bool isLoop = true);

		/**
		 * @brief アニメーション停止
		*/
		void StopAnimation() { isPlay = false; };

		/**
		 * @brief アニメーション終了しているか
		*/
		bool GetAnimationFin() { return isFin; };

		/**
		 * @brief ボーンのワールド座標取得
		*/
		Vector3 GetBonWorldPos(const uint32_t& BoneNum);

		void SetColor(Vector4 color) { color_ = color; }
		Vector4 GetColor() { return color_; }

	protected: // メンバ変数
		ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ
		// 定数バッファ(スキン)
		ComPtr<ID3D12Resource> constBuffSkin;
		// モデル
		FBXModel* fbxmodel_ = nullptr;

		std::vector<Matrix4> bonesMat;

		//1フレームの時間
		FbxTime frameTime;
		FbxTime animationTime;
		//アニメーション開始時間
		FbxTime startTime;
		//アニメーション終了時間
		FbxTime endTime;
		//現在時間(アニメーション)
		FbxTime currentTime;
		int frame = 0;
		//アニメーション再生中
		bool isPlay = false;
		//アニメーションループ
		bool isLoop_;
		//アニメーション終了
		bool isFin;
		
		// 色
		Vector4 color_ = { 1,1,1,1 };

	public:
		Transform wtf;
	};
}