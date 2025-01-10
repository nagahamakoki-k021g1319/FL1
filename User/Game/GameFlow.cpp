#include "GameFlow.h"
#include"Input.h"

void GameFlow::Initialize(){
	player_.Initilize();

	lesson_ = std::make_unique<Lesson>();
	lesson_->SetPlayer(&player_);
	lesson_->Initialize(6, 60, 90,0);

	
	isEndSchedule_ = false;

	scheduleCount_ = 1;
	schedule_[0] = 1;
	schedule_[1] = 1;
	schedule_[2] = 1;
	schedule_[3] = 1;
	schedule_[4] = 1;
	schedule_[5] = 1;
}

void GameFlow::Update(){
	if (lesson_->GetIsLessonEnd() == true) {
		//----次のスケジュールへ-----
		if (scheduleCount_ < scheduleNum_) {
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
		}
		//--------全スケジュール終了時------
		else {
			isEndSchedule_ = true;
		}
	//---レッスン中------
	}else {
		lesson_->Update();
	}
}

void GameFlow::Draw(){
	if (lesson_->GetIsLessonEnd() == true) {
		player_.DrawStatus();
	}else {
		lesson_->Draw();
	}
}

void GameFlow::ApplyGlobalVariables()
{
}
