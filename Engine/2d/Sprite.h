/**
 * @file Sprite.h
 * @brief 画像描画クラス
 */

#pragma once
#include"SpriteCommon.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Affin.h"

using namespace MyEngine;

// 頂点データ構造体
struct Vertex
{
	Vector3 pos; // xyz座標
	Vector2 uv;  // uv座標
};
//スプライト
namespace MyEngine {
	class Sprite {
	public:
		// Microsoft::WRL::を省略
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
		// 定数バッファ用データ構造体（マテリアル）
		struct ConstBufferDataMaterial {
			Vector4 color; // 色 (RGBA)
		};
		//定数バッファ用構造体（３D変換行列）
		struct ConstBufferDataTransform {
			Matrix4 mat;	//3D変換行列
		};

		//頂点番号
		enum VertexNumber {
			LB,//左下
			LT,//左上
			RB,//右下
			RT,//右上
		};
	public:
		/**
		 * @brief 初期化
		*/
		void Initialize(SpriteCommon* spritecommon_, uint32_t textureIndex = UINT32_MAX);

		/**
		 * @brief 更新
		*/
		void Update();

		/**
		 * @brief 描画
		*/
		void Draw();

		/**
		 * @brief 座標設定
		*/
		void SetPozition(const Vector2& position_);

		/**
		 * @brief 座標取得
		*/
		const Vector2& GetPosition() const { return position; }

		/**
		 * @brief 回転設定
		*/
		void SetRotation(float rotation_);

		/**
		 * @brief 回転取得
		*/
		float GetRotation() { return rotation; }

		/**
		 * @brief 色設定
		*/
		void SetColor(const Vector4& color_) { color = color_; }

		/**
		 * @brief 色取得
		*/
		Vector4 GetColor() { return color; }

		/**
		 * @brief サイズ設定
		*/
		void SetScale(const Vector3& scale_) { scale = scale_; }

		/**
		 * @brief サイズ取得
		*/
		Vector3 GetScale() { return scale; }

		/**
		 * @brief 中心座標設定
		*/
		void SetAnchorPoint(const Vector2& anchorPoint_) { anchorPoint = anchorPoint_; }

		/**
		 * @brief 中心座標取得
		*/
		Vector2 GetAnchorPoint() { return anchorPoint; }

		/**
		 * @brief テクスチャ番号設定
		*/
		void SetTextureIndex(uint32_t texNmb) { textureIndex_ = texNmb; AdjustTextureSize(); }

		/**
		 * @brief テクスチャ番号取得
		*/
		uint32_t GetTextureIndex() { return textureIndex_; }

		/**
		 * @brief テクスチャサイズ取得
		*/
		void SetTexSize(Vector2 texSize) { textureSize = texSize; }

		/**
		 * @brief サイズ取得
		*/
		Vector2 GetTexSize() { return textureSize; }

		/**
		 * @brief 初期化
		*/
		Vector2 GetSize() { return size_; }

		/**
		 * @brief サイズ設定
		*/
		void SetSize(Vector2 size);

		/**
		 * @brief 上下反転の設定
		*/
		void SetIsFlipY(bool isFlipY);

		/**
		 * @brief 左右反転の設定
		*/
		void SetIsFlipX(bool isFlipX);
		
		/**
		 * @brief テクスチャの左上座標取得
		*/
		void SetTexLeftTop(Vector2 texLeftTop);


	private:
		/**
		 * @brief テクスチャサイズをイメージに合わせる
		*/
		void AdjustTextureSize();

		SpriteCommon* spritecomon;
		HRESULT result;
		// 頂点データ
		Vertex vertices[4] = {
			// x      y     z       u     v
			{{-0.4f, -0.7f, 0.0f}, {0.0f, 1.0f}}, // 左下
			{{-0.4f, +0.7f, 0.0f}, {0.0f, 0.0f}}, // 左上
			{{+0.4f, -0.7f, 0.0f}, {1.0f, 1.0f}}, // 右下
			{{+0.4f, +0.7f, 0.0f}, {1.0f, 0.0f}}, // 右上
		};

		// 頂点バッファビューの作成
		D3D12_VERTEX_BUFFER_VIEW vbView{};

		Matrix4 matScale;//スケーリング行列
		Matrix4 matWorld;
		Matrix4 matRot;//回転行列
		Matrix4  matTrans;//平行移動行列

		//座標
		Vector3 scale{ 0.5f, 0.5f, 1.0f };

		Vector2 size_ = { 100.0f,100.0f };

		float rotation = 0.0f;
		Vector2 position = { 0.0f, 0.0f };

		Vector4 color = { 1,1,1,1 };

		Vector2 anchorPoint = { 0.0f,0.0f };

		ComPtr<ID3D12Resource> constBuffTransform;
		ConstBufferDataTransform* constMapTransform = nullptr;

		ConstBufferDataMaterial* constMapMaterial = nullptr;

		ComPtr<ID3D12Resource> constBuffMaterial;

		Vertex vertices_[4];

		Vertex* vertMap = nullptr;

		//テクスチャ番号
		uint32_t textureIndex_ = 0;

		//テクスチャ左上座標
		Vector2 textureLeftTop = { 0.0f,0.0f };
		//テクスチャ切り出しサイズ
		Vector2 textureSize = { 100.0f,100.0f };

		Matrix4 matProjection;

		// 頂点バッファの生成
		ComPtr<ID3D12Resource> vertBuff = nullptr;

		// 左右反転
		bool isFlipX_ = false;
		// 上下反転
		bool isFlipY_ = false;
	};
}