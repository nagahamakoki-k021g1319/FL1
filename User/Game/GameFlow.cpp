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

	scheduleCount_ = 1;
	schedule_[0] = 1;
	schedule_[1] = 1;
	schedule_[2] = 1;
	schedule_[3] = 1;
	schedule_[4] = 1;
	schedule_[5] = 2;
}

void GameFlow::Update(){
	if (lesson_->GetIsLessonEnd() == true || finalTest_->GetIsLessonEnd() == true) {
		//----次のスケジュールへ-----
		if (scheduleCount_ < scheduleNum_) {
			if (schedule_[scheduleCount_] == 1) {
				if (Input::GetInstance()->TriggerKey(DIK_Q)) {
					lesson_->Initialize(6, 60, 90, 0);
					player_.DeckReset();
					player_.ScoreReset();
					scheduleCount_++;

				}
				else if (Input::GetInstance()->TriggerKey(DIK_W)) {
					lesson_->Initialize(6, 60, 90, 1);
					player_.DeckReset();
					player_.ScoreReset();
					scheduleCount_++;

				}
				else if (Input::GetInstance()->TriggerKey(DIK_E)) {
					lesson_->Initialize(6, 60, 90, 2);
					player_.DeckReset();
					player_.ScoreReset();
					scheduleCount_++;
				}
			}else if (schedule_[scheduleCount_] == 2) {
				lesson_->Initialize(6, 60, 90, 0);
				finalTest_->Initialize();
				isFinalTest_ = true;
				player_.DeckReset();
				player_.ScoreReset();
				scheduleCount_++;
			}
		}
		//--------全スケジュール終了時------
		else {
			isEndSchedule_ = true;
		}
	//---レッスン中------
	}
	else {
		if (isFinalTest_ == false) {
			lesson_->Update();
		}else {
			finalTest_->Update();
		}
	}
}

void GameFlow::Draw(){
	if (lesson_->GetIsLessonEnd() == true) {
		player_.DrawStatus();
	}else if(isFinalTest_==false) {
		lesson_->Draw();
	}else {
		finalTest_->Draw();
	}
}

void GameFlow::ApplyGlobalVariables()
{
}
