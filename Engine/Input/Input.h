/**
 * @file Input.h
 * @brief 入力状態
 */

#pragma once
#include <windows.h>
#include <wrl.h>
#include <dinput.h>
#include "WinApp.h"
#include"Controller.h"
//#define DIRECTINPUT_VERSION 0x0800 // DirectInputのバージョン指定

// 入力
namespace MyEngine {
	class Input
	{
	public:
		// namespace
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	public:
		/**
		 * @brief 初期化
		*/
		void Initialize(WinApp* winApp);

		/**
		 * @brief インスタンス取得
		*/
		static Input* GetInstance();

		/**
		 * @brief 更新
		*/
		void Update();

		/**
		 * @brief キーの押下をチェック
		*/
		bool PushKey(BYTE keyNumber);

		/**
		 * @brief キーのトリガーをチェック
		*/
		bool TriggerKey(BYTE keyNumber);

		/**
		 * @brief キーの離した瞬間
		*/
		bool ReleaseKey(BYTE keyNumber);

		//----- コントローラ- ------//

		/**
		 * @brief コントローラーボタンのトリガー入力
		*/
		bool PButtonTrigger(ControllerButton button);

		/**
		 * @brief コントローラースティックのトリガー入力
		*/
		bool PStickTrigger(ControllerStick stickInput, const float& deadRange = 0.3f, const Vector2& deadRate = { 1.0f,1.0f });

		/**
		 * @brief コントローラーボタンの入力
		*/
		bool ButtonInput(ControllerButton button);

		/**
		 * @brief コントローラースティックの入力
		*/
		bool StickInput(ControllerStick stickInput, const float& deadRange = 0.3f, const Vector2& deadRate = { 1.0f,1.0f });

		/**
		 * @brief コントローラー左スティックの入力
		*/
		bool LeftStickInput(const float& deadRange = 0.3f);

		/**
		 * @brief コントローラーボタンの離した瞬間
		*/
		bool ButtonOffTrigger(ControllerButton button);

		/**
		 * @brief コントローラースティックの離した瞬間
		*/
		bool StickOffTrigger(ControllerStick stickInput, const float& deadRange = 0.3f, const Vector2& deadRate = { 1.0f,1.0f });

		/**
		 * @brief コントローラーの左スティックのベクトル
		*/
		Vector2 GetLeftStickVec(const Vector2& deadRate = { 1.0f,1.0f });

		/**
		 * @brief コントローラーの右スティックのベクトル
		*/
		Vector2 GetRightStickVec(const Vector2& deadRate = { 1.0f,1.0f });

		/**
		 * @brief コントローラーを振動させる
		*/
		void ShakeController(const float& power, const int& span);


	private: // メンバ変数
		// キーボードのデバイス
		ComPtr<IDirectInputDevice8> keyboard_;
		// DirectInputのインスタンス
		ComPtr<IDirectInput8> directInput_;
		//コントローラー
		Controller* controller_ = nullptr;
		// 全キーの状態
		BYTE key_[256] = {};
		// 前回の全キーの状態
		BYTE keyPre_[256] = {};
		//windwsAPI
		WinApp* winApp_ = nullptr;
	};
}