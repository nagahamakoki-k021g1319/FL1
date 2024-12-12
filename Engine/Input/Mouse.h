#pragma once
//#define DIRECTINPUT_VERSION  0x0800//DirectInputのバージョン指定
#include <dinput.h>
#include <cassert>
#include <wrl.h>
#include <windows.h>
#include "WinApp.h"
#include "Vector2.h"

namespace MyEngine {
	class Mouse
	{
	public:
		//namespace省略
		template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	public:

		//初期化
		void Initialize(WinApp* winApp);
		//更新
		void Update();

		//キーを押したかをチェック
		//0　左クリック
		//1　右クリック
		//2　マウスカーソルクリック
		bool PushMouse(int mouseButton_);
		//キーのトリガーをチェック
		//0　左クリック
		//1　右クリック
		//2　マウスカーソルクリック
		bool TriggerMouse(int mouseButton_);
		//マウスのリリースをチェック
		//0　左クリック
		//1　右クリック
		//2　マウスカーソルクリック
		bool ReleaseMouse(int mouseButton_);

		//マウスの現在地
		Vector2 MousePos();

		////マウスの判定
		//bool MouseBoxRange(Vector2 boxPos, Vector2 boxRange);


	private:

		//マウスのデバイス
		IDirectInputDevice8* mouse = nullptr;
		DIMOUSESTATE CurrentMouseState;		//!< マウスの現在の入力情報
		DIMOUSESTATE PrevMouseState;			//!< マウスの一フレーム前の入力情報

		//DirectInputのインスタンス
		ComPtr<IDirectInput8> directInput;
		//WindowsAPI
		WinApp* winApp_ = nullptr;

		Vector2 mousePos;
	};
}

