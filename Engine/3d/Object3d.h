/**
 * @file Object3d.h
 * @brief obj本体
 */

#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string.h>
#include "Model.h"


#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Affin.h"

#include "Transform.h"
#include "Camera.h"
#include"LightGroup.h"


/// <summary>
/// 3Dオブジェクト
/// </summary>
namespace MyEngine {
	class Object3d
	{
	private: // エイリアス
		// Microsoft::WRL::を省略
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
		// DirectX::を省略

		// 定数バッファ用データ構造体
		struct ConstBufferDataB0 {
			Matrix4 viewProj;
			Matrix4 world;
			Vector3 cameraPos;
			unsigned int enableLighting;
		};

	private: // 定数
		static const int division = 50;					// 分割数
		static const float radius;				// 底面の半径
		static const float prizmHeight;			// 柱の高さ
		static const int planeCount = division * 2 + division * 2;		// 面の数
		static const int vertexCount = planeCount * 3;		// 頂点数

	public: // 静的メンバ関数
		/// <summary>
		/// 静的初期化
		/// </summary>
		/// <param name="device">デバイス</param>
		/// <param name="window_width">画面幅</param>
		/// <param name="window_height">画面高さ</param>
		static void StaticInitialize(ID3D12Device* device);

		/// <summary>
		/// 描画前処理
		/// </summary>
		/// <param name="cmdList">描画コマンドリスト</param>
		static void PreDraw(ID3D12GraphicsCommandList* cmdList);

		/// <summary>
		/// 描画後処理
		/// </summary>
		static void PostDraw();

		/// <summary>
		/// 3Dオブジェクト生成
		/// </summary>
		/// <returns></returns>
		static std::unique_ptr<Object3d> Create();

		/**
		 * @brief 死亡フラグ
		*/
		bool IsDead() const { return  isDead_; }

		static void SetLight(LightGroup* lightGroup) { lightGroup_ = lightGroup; }
		void SetLightingActive(bool active) {lightingActive_ = active; }

	private: // 静的メンバ変数
		// デバイス
		static ComPtr<ID3D12Device> device;

		// コマンドリスト
		static ComPtr<ID3D12GraphicsCommandList> cmdList_;
		// ルートシグネチャ
		static ComPtr<ID3D12RootSignature> rootsignature;
		// パイプラインステートオブジェクト
		static ComPtr<ID3D12PipelineState> pipelinestate;

		static LightGroup* lightGroup_;

		// ビュー行列
		static Matrix4 matView;
		// 射影行列
		static Matrix4 matProjection;
		// 視点座標
		static Vector3 eye;
		// 注視点座標
		static Vector3 target;
		// 上方向ベクトル
		static Vector3 up;


		static float focalLengs;

	private:// 静的メンバ関数

		/// <summary>
		/// カメラ初期化
		/// </summary>
		/// <param name="window_width">画面横幅</param>
		/// <param name="window_height">画面縦幅</param>
		static void InitializeCamera();

		/// <summary>
		/// グラフィックパイプライン生成
		/// </summary>
		/// <returns>成否</returns>
		static void InitializeGraphicsPipeline();

		/// <summary>
		/// ビュー行列を更新
		/// </summary>
		static void UpdateViewMatrix();

	public: // メンバ関数

		Object3d();
		~Object3d();

		bool Initialize();
		/// <summary>
		/// 毎フレーム処理
		/// </summary>
		void Update();
		void Update(Transform* parentWtf);

		void UpdateMat();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		Object3d* GetParent() const { return parent_; }

		void SetParent(Object3d* parent) { this->parent_ = parent; }
		static void SetCamera(Camera* camera) { Object3d::camera_ = camera; }

		//setter
		void SetModel(Model* model) { this->model_ = model; }

		void SetColor(Vector4 color) { color_ = color; }
		Vector4 GetColor() { return color_; }

	private: // メンバ変数
	public:
		ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ

		bool isDead_ = false;

		// 色
		Vector4 color_ = { 1,1,1,1 };

		// 親オブジェクト
		Object3d* parent_ = nullptr;
		//モデル
		Model* model_ = nullptr;
		static Camera* camera_;
		bool lightingActive_ = true;

		static float win_wi, win_hi;
	public:
		Transform wtf;

	};
}