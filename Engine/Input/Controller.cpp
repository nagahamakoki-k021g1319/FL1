/**
 * @file Controller.cpp
 * @brief Xboxコントローラー
 */

#include "Controller.h"
#include <assert.h>
#include <winerror.h>

using namespace MyEngine;

Controller::Controller() {}
Controller::~Controller() {}

bool Controller::StickInDeadZone(Vector2& Thumb, const Vector2& DeadRate)
{
	bool x = false;
	bool y = false;

	if ((Thumb.x < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.x
		&& Thumb.x > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.x))
	{
		Thumb.x = 0.0f;
		x = true;
	}
	if ((Thumb.y < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.y
		&& Thumb.y > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.y))
	{
		Thumb.y = 0.0f;
		y = true;
	}

	if (x && y)
	{
		return true;
	}

	return false;
}

void Controller::Update()
{
	oldXinputState_ = xinputState_;
	ZeroMemory(&xinputState_, sizeof(XINPUT_STATE));

	//コントローラー取得
	DWORD dwResult = XInputGetState(0, &xinputState_);

	const float maxValue = 65535.0f;

	if (dwResult == ERROR_SUCCESS)
	{
		//コントローラーが接続されている
		if (0 < shakeTimer_)
		{
			shakeTimer_--;
			XINPUT_VIBRATION vibration;
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

			if (shakeTimer_ == 0)
			{
				vibration.wLeftMotorSpeed = static_cast<WORD>(0.0f); // use any value between 0-65535 here
				vibration.wRightMotorSpeed = static_cast<WORD>(0.0f); // use any value between 0-65535 here
			}
			else
			{
				vibration.wLeftMotorSpeed = static_cast<WORD>(maxValue * shakePower_); // use any value between 0-65535 here
				vibration.wRightMotorSpeed = static_cast<WORD>(maxValue * shakePower_); // use any value between 0-65535 here
			}

			XInputSetState(dwResult, &vibration);
		}
	}
	else
	{
		//コントローラーが接続されていない
	}
}

bool Controller::ButtonTrigger(ControllerButton button)
{
	//トリガー
	if (button == LT)
	{
		return oldXinputState_.Gamepad.bLeftTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && ButtonInput(button);
	}
	else if (button == RT)
	{
		return oldXinputState_.Gamepad.bRightTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && ButtonInput(button);
	}
	else
	{
		return !(oldXinputState_.Gamepad.wButtons & button) && ButtonInput(button);
	}
}

bool Controller::StickTrigger(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate)
{
	Vector2 oldVec;
	Vector2 vec;
	bool isLeftStick = stickInput <= L_RIGHT;
	if (isLeftStick)
	{
		oldVec = Vector2(oldXinputState_.Gamepad.sThumbLX, oldXinputState_.Gamepad.sThumbLY);
		vec = Vector2(xinputState_.Gamepad.sThumbLX, xinputState_.Gamepad.sThumbLY);
	}
	else
	{
		oldVec = Vector2(oldXinputState_.Gamepad.sThumbRX, oldXinputState_.Gamepad.sThumbRY);
		vec = Vector2(xinputState_.Gamepad.sThumbRX, xinputState_.Gamepad.sThumbRY);
	}

	if (!StickInDeadZone(oldVec, deadRate))
	{
		return false;
	}

	if (StickInDeadZone(vec, deadRate))
	{
		return false;
	}

	bool result = false;

	if (stickInput % 4 == L_UP)
	{
		result = !(deadRange < (oldVec.y / STICK_INPUT_MAX)) && deadRange < (vec.y / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_DOWN)
	{
		result = !(oldVec.y / STICK_INPUT_MAX < -deadRange) && vec.y / STICK_INPUT_MAX < -deadRange;
	}
	else if (stickInput % 4 == L_RIGHT)
	{
		result = !(deadRange < (oldVec.x / STICK_INPUT_MAX)) && deadRange < (vec.x / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_LEFT)
	{
		result = !(oldVec.x / STICK_INPUT_MAX < -deadRange) && vec.x / STICK_INPUT_MAX < -deadRange;
	}
	else
	{
		assert(0);
	}

	return result;
}

bool Controller::ButtonInput(ControllerButton button)
{
	if (button == LT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < xinputState_.Gamepad.bLeftTrigger;
	}
	else if (button == RT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < xinputState_.Gamepad.bRightTrigger;
	}
	else
	{
		return xinputState_.Gamepad.wButtons & button;
	}
}

bool Controller::StickInput(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate)
{
	Vector2 vec;
	bool isLeftStick = stickInput <= L_RIGHT;

	if (isLeftStick)
	{
		vec = Vector2(xinputState_.Gamepad.sThumbLX, xinputState_.Gamepad.sThumbLY);
	}
	else
	{
		vec = Vector2(xinputState_.Gamepad.sThumbRX, xinputState_.Gamepad.sThumbRY);
	}

	if (StickInDeadZone(vec, deadRate))return false;

	if (stickInput % 4 == L_UP)
	{
		return deadRange < (vec.y / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_DOWN)
	{
		return  vec.y / STICK_INPUT_MAX < -deadRange;
	}
	else if (stickInput % 4 == L_RIGHT)
	{
		return deadRange < (vec.x / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_LEFT)
	{
		return  vec.x / STICK_INPUT_MAX < -deadRange;
	}

	assert(0);
	return false;
}

bool Controller::LeftStickInput(const float& deadRange) {
	Vector2 stickVec = { float(xinputState_.Gamepad.sThumbLX),float(xinputState_.Gamepad.sThumbLY) };

	float depth = stickVec.length();

	if (depth > STICK_INPUT_MAX * deadRange) {
		return true;
	}

	return false;
}

bool Controller::ButtonOffTrigger(ControllerButton button)
{
	//トリガー
	if (button == LT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < oldXinputState_.Gamepad.bLeftTrigger && !ButtonInput(button);
	}
	else if (button == RT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < oldXinputState_.Gamepad.bRightTrigger && !ButtonInput(button);
	}
	//ボタン
	else
	{
		return (oldXinputState_.Gamepad.wButtons & button) && !ButtonInput(button);
	}
}

bool Controller::StickOffTrigger(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate)
{
	Vector2 oldVec;
	Vector2 vec;
	bool isLeftStick = stickInput <= L_RIGHT;

	if (isLeftStick)
	{
		oldVec = Vector2(oldXinputState_.Gamepad.sThumbLX, oldXinputState_.Gamepad.sThumbLY);
		vec = Vector2(xinputState_.Gamepad.sThumbLX, xinputState_.Gamepad.sThumbLY);
	}
	else
	{
		oldVec = Vector2(oldXinputState_.Gamepad.sThumbRX, oldXinputState_.Gamepad.sThumbRY);
		vec = Vector2(xinputState_.Gamepad.sThumbRX, xinputState_.Gamepad.sThumbRY);
	}

	if (!StickInDeadZone(oldVec, deadRate))
	{
		return false;
	}

	if (StickInDeadZone(vec, deadRate))
	{
		return false;
	}

	bool result = false;

	if (stickInput % 4 == L_UP)
	{
		result = deadRange < (oldVec.y / STICK_INPUT_MAX) && !(deadRange < (vec.y / STICK_INPUT_MAX));
	}
	else if (stickInput % 4 == L_DOWN)
	{
		result = oldVec.y / STICK_INPUT_MAX < -deadRange && !(vec.y / STICK_INPUT_MAX < -deadRange);
	}
	else if (stickInput % 4 == L_RIGHT)
	{
		result = deadRange < (oldVec.x / STICK_INPUT_MAX) && !(deadRange < (vec.x / STICK_INPUT_MAX));
	}
	else if (stickInput % 4 == L_LEFT)
	{
		result = oldVec.x / STICK_INPUT_MAX < -deadRange && !(vec.x / STICK_INPUT_MAX < -deadRange);
	}
	else
	{
		assert(0);
	}

	return result;
}

Vector2 Controller::GetLeftStickVec(const Vector2& deadRate)
{
	Vector2 result(static_cast<float>(xinputState_.Gamepad.sThumbLX), static_cast<float>(xinputState_.Gamepad.sThumbLY));
	StickInDeadZone(result, deadRate);
	return result / STICK_INPUT_MAX;
}

Vector2 Controller::GetRightStickVec(const Vector2& deadRate)
{
	Vector2 result(static_cast<float>(xinputState_.Gamepad.sThumbRX), static_cast<float>(xinputState_.Gamepad.sThumbRY));
	StickInDeadZone(result, deadRate);
	return result / STICK_INPUT_MAX;
}

void Controller::ShakeController(const float& power, const int& span)
{
	if (!(0 < power && power <= 1.0f))
	{
		assert(0);
	}

	shakePower_ = power;
	shakeTimer_ = span;
}