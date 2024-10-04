#include "GoalMovie.h"
#include "Easing.h"
#include "TGameCamera.h"

GoalMovie::GoalMovie()
{
	isFinish_ = false;
}

void GoalMovie::Init()
{
	BaseMovie::Init();
	phaseTimer_ = 0;
	MovieBarInInit();
}

void GoalMovie::Update(TGameCamera* camera)
{
	phaseTime_ = 120.0f;

	phaseTimer_++;

	float rotAngle = Easing::OutQuad(0.0f, 180.0f, phaseTimer_ / phaseTime_);

	const float radian = DirectX::XMConvertToRadians(rotAngle);
	const float distance = -20.0f;

	camera->SetEye({ distance * sinf(radian), 4.0f, distance * cosf(radian) });

	BaseMovie::Update(camera);

	if (phaseTimer_ >= phaseTime_) {
		MovieBarOutInit();
		isFinish_ = true;
	}
}
