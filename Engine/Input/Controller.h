/**
 * @file Controller.h
 * @brief Xboxコントローラー
 */

#pragma once
#include <windows.h>
#include "Vector2.h"
#include <xinput.h>
#pragma comment (lib, "xinput.lib")

enum ControllerButton
{
	B = XINPUT_GAMEPAD_B,
	A = XINPUT_GAMEPAD_A,
	X = XINPUT_GAMEPAD_X,
	Y = XINPUT_GAMEPAD_Y,
	START = XINPUT_GAMEPAD_START,
	BACK = XINPUT_GAMEPAD_BACK,
	LB = XINPUT_GAMEPAD_LEFT_SHOULDER,
	RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	LSTICK = XINPUT_GAMEPAD_LEFT_THUMB,
	RSTICK = XINPUT_GAMEPAD_RIGHT_THUMB,
	LT,
	RT,
};

enum ControllerStick
{
	L_UP, L_DOWN, L_LEFT, L_RIGHT,
	R_UP, R_DOWN, R_LEFT, R_RIGHT, XBOX_STICK_NUM
};

namespace MyEngine {
	class Controller
	{
	private:

		XINPUT_STATE xinputState_{};
		XINPUT_STATE oldXinputState_{};

		//コントローラー振動強さ
		float shakePower_ = 0.0f;
		//コントローラー振動長さ(フレーム数)
		int shakeTimer_ = 0;

		//デッドゾーンに入っているか(DeadRate : デッドゾーン判定の度合い、1.0fだとデフォルト)
		bool StickInDeadZone(Vector2& thumb, const Vector2& deadRate);

		//コピーコンストラクタ・代入演算子削除
		Controller& operator=(const Controller&) = delete;
		Controller(const Controller&) = delete;

		//最高入力強度
		const float STICK_INPUT_MAX = 32768.0f;

	public:
		Controller();
		~Controller();

		/**
		 * @brief 更新
		*/
		void Update();

		/**
		 * @brief コントローラーボタンのトリガー入力
		*/
		bool ButtonTrigger(ControllerButton button);

		/**
		 * @brief コントローラースティックのトリガー入力
		*/
		bool StickTrigger(ControllerStick stickInput, const float& deadRange = 0.3f, const Vector2& deadRate = { 1.0f,1.0f });

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
	};
}