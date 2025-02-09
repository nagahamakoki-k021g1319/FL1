#pragma once
#include "Lesson.h"
#include "Consult.h"
#include "FinalTest.h"

#include"Player.h"
#include "Game/Lesson.h"
#include"FinalTest.h"
#include"Button.h"
#include "Audio.h"


class GameFlow{
public:
	void Initialize();

	void Update();

	void Draw();

	void ApplyGlobalVariables();

	bool IsEndSchedule() { return isEndSchedule_; };
	bool IsRetire();
private:
	Player player_;
	
	unique_ptr<Lesson> lesson_ = nullptr;
	unique_ptr<FinalTest> finalTest_ = nullptr;

	const int scheduleNum_ = 6;
	int scheduleCount_;
	int schedule_[6];
	bool isEndSchedule_;
	bool isFinalTest_;
	bool isFirstPick_;

	bool bgmStart_;

	int perfectScore[4];
	int spPerfectScore[4];
	bool isSp_[3];

	unique_ptr<Button> voButton_ = nullptr;
	unique_ptr<Button> daButton_ = nullptr;
	unique_ptr<Button> viButton_ = nullptr;

	Audio* audio_ = nullptr;
	IXAudio2SourceVoice* pSourceVoice_;

	bool isBGMStart = false;

	unique_ptr<Sprite> schedulePng_ = nullptr;
	unique_ptr<Sprite> spPng_[3];
	unique_ptr<Button> retire_ = nullptr;
	unique_ptr<Sprite> selectBackGround_ = nullptr;
};

