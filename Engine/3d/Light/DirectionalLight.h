/**
 * @file DirectionalLight.h
 * @brief ライト
 */

#pragma once
#include <d3d12.h>
#include <wrl.h>
#include"Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace MyEngine {
	class DirectionalLight {
	public:
		static void StaticInitialize(ID3D12Device* device) { device_ = device; }
		static DirectionalLight* Create();

		void Initialize();
		void Update();
		void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

		void TransferConstBuffer();
		void SetLightDir(const Vector4& lightdirs);
		void SetLightColor(const Vector3& lightcolors);
		inline void SetActive(bool actives) { active_ = actives; }

		inline bool IsActive() { return active_; }
		Vector4 GetLightDir() { return lightDir_; }
		Vector3 GetLightColor() { return lightColor_; }

	public:
		//定数バッファ用データ構造体
		struct ConstBufferData{
			Vector4 lightVec;
			Vector3 lightColor;
			unsigned int active;
		};
	private:
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
		static ID3D12Device* device_;
		HRESULT result;
		ComPtr<ID3D12Resource> constBuff;
		Vector4 lightDir_ = { 1,0,0,0 };
		Vector3 lightColor_ = { 1,1,1 };
		bool dirty_ = false;
		bool active_ = false;
	};
}