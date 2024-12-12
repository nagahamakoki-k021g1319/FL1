#include "Mouse.h"

void MyEngine::Mouse::Initialize(WinApp* winApp)
{
	HRESULT result;
	//借りてきたWinAppのインスタンスを記録
	winApp_ = winApp;
	result = DirectInput8Create(
		winApp_->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr);
	//マウスデバイスの生成
	result = directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
	assert(SUCCEEDED(result));
	//入力データ形式のセット
	result = mouse->SetDataFormat(&c_dfDIMouse);
	assert(SUCCEEDED(result));
	//排他的制御レベルのセット
	result = mouse->SetCooperativeLevel(
		winApp_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}


void MyEngine::Mouse::Update()
{
	HRESULT result;

	// 更新前に最新マウス情報を保存する
	PrevMouseState = CurrentMouseState;
	// 最新のマウスの状態を更新
	result = mouse->GetDeviceState(sizeof(DIMOUSESTATE), &CurrentMouseState);
	if (FAILED(result))
	{
		mouse->Acquire();
		result = mouse->GetDeviceState(sizeof(DIMOUSESTATE), &CurrentMouseState);
	}

	POINT mousePosition;
	//マウス座標（スクリーン座標）を取得する
	GetCursorPos(&mousePosition);

	//クライアントエリア座標に変換する
	assert(winApp_);
	HWND hwnd = winApp_->GetHwnd();
	assert(hwnd);
	ScreenToClient(hwnd, &mousePosition);

	//マウス座標を2Dレティクルのスプライトに代入する
	mousePos = (Vector2(static_cast<float> (mousePosition.x), static_cast<float> (mousePosition.y)));
}

bool MyEngine::Mouse::PushMouse(int mouse_)
{
	// 左クリックされているか判定
	if (CurrentMouseState.rgbButtons[mouse_] & (0x80))
	{
		// 左クリック中
		return true;
	}

	return false;
}

bool MyEngine::Mouse::TriggerMouse(int mouse_)
{
	if (!(PrevMouseState.rgbButtons[mouse_] & (0x80)) &&
		CurrentMouseState.rgbButtons[mouse_] & (0x80))
	{
		return true;
	}


	return false;
}

bool MyEngine::Mouse::ReleaseMouse(int mouse_)
{
	if (PrevMouseState.rgbButtons[mouse_] & (0x80) &&
		!(CurrentMouseState.rgbButtons[mouse_] & (0x80)))
	{
		return true;
	}

	return false;
}

MyEngine::Vector2 MyEngine::Mouse::MousePos()
{

	return mousePos;
}

//bool MyEngine::Mouse::MouseBoxRange(Vector2 boxPos, Vector2 boxRange)
//{
//	Vector2 range1 = { boxPos - boxRange };
//	Vector2 range2 = { boxPos + boxRange };
//
//	/*if (range1.x <= mousePos.x <= range2.x && range1.y <= mousePos.y <= range2.y) {
//		return true;
//	}*/
//
//
//	return false;
//}
