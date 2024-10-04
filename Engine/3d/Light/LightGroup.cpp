/**
 * @file LightGroup.cpp
 * @brief ライト
 */

#include"LightGroup.h"

using namespace MyEngine;
ID3D12Device* LightGroup::device_ = nullptr;

void LightGroup::Initialize(){
	DefaultLightSetting();
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
		&cbHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff));
	assert(SUCCEEDED(result));

	TransferConstBuffer();
}
LightGroup* LightGroup::GetInstance() {
	static LightGroup instance;
	return &instance;
}

void LightGroup::Update(){
	TransferConstBuffer();
}

void LightGroup::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex) {
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex, constBuff->GetGPUVirtualAddress());
}

void LightGroup::TransferConstBuffer(){
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result))
	{
		constMap->ambientColor = ambientColor_;

		//ライト
		for (int i = 0; i < DirLightNum; i++){
			if (dirLights_[i].IsActive()){
				constMap->dirLights[i].active = 1;
				constMap->dirLights[i].lightVec = dirLights_[i].GetLightDir();
				constMap->dirLights[i].lightColor = dirLights_[i].GetLightColor();
			}else{
				constMap->dirLights[i].active = 0;
			}
		}

		//丸影
		std::forward_list<CircleShadow*>::iterator it;
		it = circleShadows_.begin();
		int circleShadowIndex = 0;
		for (; it != circleShadows_.end(); ++it) {
			CircleShadow* circleShadow = *it;
			if (circleShadow->IsActive()) {
				constMap->circleShadows[circleShadowIndex].active = 1;
				constMap->circleShadows[circleShadowIndex].dir = -circleShadow->GetDir();
				constMap->circleShadows[circleShadowIndex].casterPos = circleShadow->GetCasterPos();
				constMap->circleShadows[circleShadowIndex].distanceCasterLight = circleShadow->GetDistanceCasterLight();
				constMap->circleShadows[circleShadowIndex].atten = circleShadow->GetAtten();
				constMap->circleShadows[circleShadowIndex].factorAngleCos = circleShadow->GetFactorAngleCos();
			}else{
				constMap->circleShadows[circleShadowIndex].active = 0;
			}
			circleShadowIndex++;
		}
		for (int i = circleShadowIndex; i < CircleShadowNum; i++) {
			constMap->circleShadows[circleShadowIndex].active = 0;
		}

		constBuff->Unmap(0, nullptr);
	}
}

void LightGroup::SetAmbientColor(const Vector3& color) {
	ambientColor_ = color;
	dirty_ = true;
}

void LightGroup::SetDirLightActive(int index, bool active) {
	assert(0 <= index && index < DirLightNum);
	dirLights_[index].SetActive(active);
}

void LightGroup::SetDirLightDir(int index, Vector4& lightDir) {
	assert(0 <= index && index < DirLightNum);
	dirLights_[index].SetLightDir(lightDir);
	dirty_ = true;
}

void LightGroup::SetDirLightColor(int index, Vector3& lightColor) {
	assert(0 <= index && index < DirLightNum);
	dirLights_[index].SetLightColor(lightColor);
	dirty_ = true;
}

void LightGroup::DefaultLightSetting() {
	dirLights_[0].SetActive(true);
	dirLights_[0].SetLightColor({ 1, 1, 1 });
	dirLights_[0].SetLightDir({ 0,1,-1,0 });

	dirLights_[1].SetActive(false);
	dirLights_[1].SetLightColor({ 1, 1, 1 });
	dirLights_[1].SetLightDir({ 0,-1,0,0 });

	dirLights_[2].SetActive(false);
	dirLights_[2].SetLightColor({ 1, 1, 1 });
	dirLights_[2].SetLightDir({ 1,1,0,0 });
}