#include "GameFlow.h"
#include"Input.h"

void GameFlow::Initialize(){
	player_.Initilize();

	lesson_ = std::make_unique<Lesson>();
	lesson_->SetPlayer(&player_);
	lesson_->Initialize(6, 60, 2);

	finalTest_ = std::make_unique<FinalTest>();
	finalTest_->SetPlayer(&player_);
	finalTest_->Initialize();
	
	isEndSchedule_ = false;
	isFinalTest_ = false;
	isFirstPick_ = true;

	scheduleCount_ = 0;
	schedule_[0] = 0;
	schedule_[1] = 0;
	schedule_[2] = 1;
	schedule_[3] = 2;
	schedule_[4] = 3;
	schedule_[5] = 4;


	perfectScore[0] = 60;
	perfectScore[1] = 110;
	perfectScore[2] = 120;
	perfectScore[3] = 150;

	spPerfectScore[0] = 90;
	spPerfectScore[1] = 170;
	spPerfectScore[2] = 200;
	spPerfectScore[3] = 220;

	isSp_[0] = false;
	isSp_[1] = false;
	isSp_[2] = false;
}

void GameFlow::Update(){
	if (lesson_->GetIsLessonEnd() == false && isFirstPick_ == false) {
		lesson_->Update();
		for (int i = 0; i < 3; i++) {
			if (rand() % 3 == 0) {
				isSp_[i] = true;
			}else {
				isSp_[i] = false;
			}
		}
	}else if ((lesson_->GetIsLessonEnd() == true && isFinalTest_ == false) || isFirstPick_ == true) {
		if (scheduleCount_ < scheduleNum_) {
			if (schedule_[scheduleCount_] == 0 || schedule_[scheduleCount_] == 1|| schedule_[scheduleCount_] == 2|| schedule_[scheduleCount_] == 3) {
				if (Input::GetInstance()->TriggerKey(DIK_Q)) {
					if (isSp_[0] == true) {
						lesson_->Initialize(6, spPerfectScore[schedule_[scheduleCount_]], 0);
					}else {
						lesson_->Initialize(6, perfectScore[schedule_[scheduleCount_]], 0);
					}
					player_.DeckReset();
					player_.ScoreReset();
					scheduleCount_++;
					isFirstPick_ = false;
				}else if (Input::GetInstance()->TriggerKey(DIK_W)) {
					if (isSp_[1] == true) {
						lesson_->Initialize(6, spPerfectScore[schedule_[scheduleCount_]], 1);
					}else {
						lesson_->Initialize(6, perfectScore[schedule_[scheduleCount_]], 1);
					}
					player_.DeckReset();
					player_.ScoreReset();
					scheduleCount_++;
					isFirstPick_ = false;
				}else if (Input::GetInstance()->TriggerKey(DIK_E)) {
					if (isSp_[2] == true) {
						lesson_->Initialize(6, spPerfectScore[schedule_[scheduleCount_]], 2);
					}else {
						lesson_->Initialize(6, perfectScore[schedule_[scheduleCount_]], 2);
					}
					player_.DeckReset();
					player_.ScoreReset();
					scheduleCount_++;
					isFirstPick_ = false;
				}
			}
		}
	}else if (isFinalTest_ == true) {
		finalTest_->Update();
		if (finalTest_->GetIsLessonEnd() == true) {
			isEndSchedule_ = true;
		}
	}

	if (lesson_->GetIsLessonEnd() == true && isFinalTest_ == false) {
		if (schedule_[scheduleCount_] == 4) {
			finalTest_->Initialize();
			isFinalTest_ = true;
			player_.DeckReset();
			player_.ScoreReset();
			scheduleCount_++;
			player_.Heal(20);
		}
	}
}

void GameFlow::Draw(){
	if (lesson_->GetIsLessonEnd() == false && isFirstPick_ == false) {
		lesson_->Draw();
	}else if ((lesson_->GetIsLessonEnd() == true && isFinalTest_ == false) || isFirstPick_ == true) {
		player_.DrawStatus();
	}else if (isFinalTest_ == true) {
		finalTest_->Draw();
	}
}

void GameFlow::ApplyGlobalVariables()
{
}
