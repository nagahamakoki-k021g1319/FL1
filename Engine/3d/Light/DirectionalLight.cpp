/**
 * @file DirectionalLight.cpp
 * @brief ライト
 */

#include"DirectionalLight.h"

using namespace MyEngine;
ID3D12Device* DirectionalLight::device_ = nullptr;

void DirectionalLight::Initialize() {
	// ヒープ設定
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	// リソース設定
	D3D12_RESOURCE_DESC cbResourceDesc{};
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferData) + 0xff) & ~0xff;
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	// 定数バッファの生成
	result = device_->CreateCommittedResource(
		&cbHeapProp, // ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc, // リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff));
	assert(SUCCEEDED(result));
	//定数バッファへデータ転送
	TransferConstBuffer();
}

void DirectionalLight::TransferConstBuffer(){
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->lightVec = -lightDir_;
		constMap->lightColor = lightColor_;
		constBuff->Unmap(0, nullptr);
	}
}

void DirectionalLight::SetLightDir(const Vector4& lightdirs){
	lightDir_ = lightdirs.Normalization();
	dirty_ = true;
}

void DirectionalLight::SetLightColor(const Vector3& lightcolors){
	lightColor_ = lightcolors;
	dirty_ = true;
}

void DirectionalLight::Update(){
	if (dirty_) {
		TransferConstBuffer();
		dirty_ = false;
	}
}

void DirectionalLight::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex){
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex,
		constBuff->GetGPUVirtualAddress());
}

DirectionalLight* DirectionalLight::Create(){
	//3Dオブジェクトのインスタンスを生成
	DirectionalLight* instance = new DirectionalLight();
	//初期化
	instance->Initialize();
	//生成したインスタンスを渡す
	return instance;
}