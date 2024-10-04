/**
 * @file Input.cpp
 * @brief 入力状態
 */

#include "Input.h"
#include <cassert>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//using namespace Microsoft::WRL;
using namespace MyEngine;

void Input::Initialize(WinApp* winApp)
{
	this->winApp_ = winApp;


	HRESULT result;

	// DirectInputのインスタンス生成
	/*ComPtr<IDirectInput8> directInput = nullptr;*/
	result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput_, nullptr);
	assert(SUCCEEDED(result));

	// キーボードデバイスの生成
	//ComPtr<IDirectInputDevice8> keyboard = nullptr;
	result = directInput_->CreateDevice(GUID_SysKeyboard, &keyboard_, NULL);
	assert(SUCCEEDED(result));

	// 入力データ形式のセット
	result = keyboard_->SetDataFormat(&c_dfDIKeyboard); // 標準形式
	assert(SUCCEEDED(result));

	// 排他制御レベルのセット
	result = keyboard_->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

	//コントローラーの初期化
	controller_ = new Controller;
}

Input* Input::GetInstance() {
	static Input instance;
	return &instance;
}

void Input::Update()
{
	HRESULT result;

	// 前回のキー入力を保持
	memcpy(keyPre_, key_, sizeof(key_));

	// キーボード情報の取得開始
	result = keyboard_->Acquire();

	// 全キーの入力状態を取得する
	/*BYTE key[256] = {};*/
	result = keyboard_->GetDeviceState(sizeof(key_), key_);

	//コントローラーデバイスの更新
	controller_->Update();
}

bool Input::PushKey(BYTE keyNumber)
{
	// 指定キーを押していればtrueを返す
	if (key_[keyNumber]) {
		return true;
	}
	// そうではなければfalseを返す
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	if (key_[keyNumber])
	{
		if (keyPre_[keyNumber]) {
			return false;
		}
		return true;
	}

	return false;
}

/// <summary>
/// キーのトリガーをチェック
/// </summary>
/// </param name="keyNumber">キー番号( DIK_0 等)</param>
/// <reutrns>離されたか</params>
bool Input::ReleaseKey(BYTE keyNumber) {
	if (keyPre_[keyNumber])
	{
		if (key_[keyNumber]) {
			return false;
		}
		return true;
	}

	return false;
}

bool Input::PButtonTrigger(ControllerButton button)
{
	return controller_->ButtonTrigger(button);
}

bool Input::PStickTrigger(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate)
{
	return controller_->StickTrigger(stickInput, deadRange, deadRate);
}

bool Input::ButtonInput(ControllerButton button)
{
	return controller_->ButtonInput(button);
}

bool Input::StickInput(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate)
{
	return controller_->StickInput(stickInput, deadRange, deadRate);
}

bool Input::LeftStickInput(const float& deadRange) {
	return controller_->LeftStickInput(deadRange);
}

bool Input::ButtonOffTrigger(ControllerButton button)
{
	return controller_->ButtonOffTrigger(button);
}

bool Input::StickOffTrigger(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate)
{
	return controller_->StickOffTrigger(stickInput, deadRange, deadRate);
}

Vector2 Input::GetLeftStickVec(const Vector2& deadRate)
{
	return  controller_->GetLeftStickVec(deadRate);
}

Vector2 Input::GetRightStickVec(const Vector2& deadRate)
{
	return controller_->GetRightStickVec(deadRate);
}

void Input::ShakeController(const float& power, const int& span)
{
	controller_->ShakeController(power, span);
}
