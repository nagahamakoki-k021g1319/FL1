#include "GameFlow.h"
#include"Input.h"

void GameFlow::Initialize(){
	player_.Initilize();

	lesson_ = std::make_unique<Lesson>();
	lesson_->SetPlayer(&player_);
	lesson_->Initialize(6, 60, 90, 2);

	finalTest_ = std::make_unique<FinalTest>();
	finalTest_->SetPlayer(&player_);
	finalTest_->Initialize();
	
	isEndSchedule_ = false;
	isFinalTest_ = false;
	isFirstPick_ = true;

	scheduleCount_ = 0;
	schedule_[0] = 1;
	schedule_[1] = 1;
	schedule_[2] = 1;
	schedule_[3] = 1;
	schedule_[4] = 1;
	schedule_[5] = 2;
}

void GameFlow::Update(){
	if (lesson_->GetIsLessonEnd() == false && isFirstPick_ == false) {
		lesson_->Update();
	}else if ((lesson_->GetIsLessonEnd() == true && isFinalTest_ == false) || isFirstPick_ == true) {
		if (scheduleCount_ < scheduleNum_) {
			if (schedule_[scheduleCount_] == 1) {
				if (Input::GetInstance()->TriggerKey(DIK_Q)) {
					lesson_->Initialize(6, 60, 90, 0);
					player_.DeckReset();
					player_.ScoreReset();
					scheduleCount_++;
					isFirstPick_ = false;
				}else if (Input::GetInstance()->TriggerKey(DIK_W)) {
					lesson_->Initialize(6, 60, 90, 1);
					player_.DeckReset();
					player_.ScoreReset();
					scheduleCount_++;
					isFirstPick_ = false;
				}else if (Input::GetInstance()->TriggerKey(DIK_E)) {
					lesson_->Initialize(6, 60, 90, 2);
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
		if (schedule_[scheduleCount_] == 2) {
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
