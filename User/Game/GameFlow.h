#pragma once
#include "Lesson.h"
#include "Consult.h"
#include "FinalTest.h"

#include"Player.h"
#include "Game/Lesson.h"
#include"FinalTest.h"


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
	unique_ptr<FinalTest> finalTest_ = nullptr;

	const int scheduleNum_ = 6;
	int scheduleCount_;
	int schedule_[6];
	bool isEndSchedule_;
	bool isFinalTest_;
};

