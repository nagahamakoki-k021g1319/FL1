#pragma once
#include "Lesson.h"
#include "Consult.h"
#include "FinalTest.h"

#include"Player.h"
#include "Game/Lesson.h"


class GameFlow{
public:
	void Initialize();

	void Update();

	void Draw();

	void ApplyGlobalVariables();

	bool IsEndSchedule() { return isEndSchedule_; };
private:
	Player player_;
	
	unique_ptr<Lesson> lesson_ = nullptr;

	const int scheduleNum_ = 2;
	int scheduleCount_;
	int schedule_[6];
	bool isEndSchedule_;
};

