#include "GameFlow.h"
#include"Input.h"

void GameFlow::Initialize(){
	player_.Initilize();

	lesson_ = std::make_unique<Lesson>();
	lesson_->Initialize(6, 60, 90,0);

	lesson_->SetPlayer(&player_);


	hpShieldUI_ = make_unique<HpShieldUI>();
	hpShieldUI_->GetHPpt(player_.GetHP());
	hpShieldUI_->GetShieldpt(player_.GetShield());
	hpShieldUI_->Initialize();

	bufUI_ = make_unique<BufUI>();
	bufUI_->Initialize();
}

void GameFlow::Update(){
	if (lesson_->GetIsLessonEnd() == true) {
		if(Input::GetInstance()->TriggerKey(DIK_Q)) {
			lesson_->Initialize(6, 60, 90,0);
			player_.DeckReset();
			player_.ScoreReset();

		}else if (Input::GetInstance()->TriggerKey(DIK_W)) {
			lesson_->Initialize(6, 60, 90,1);
			player_.DeckReset();
			player_.ScoreReset();

		}else if (Input::GetInstance()->TriggerKey(DIK_E)) {
			lesson_->Initialize(6, 60, 90,2);
			player_.DeckReset();
			player_.ScoreReset();
		}
	}else {
		lesson_->Update();
		hpShieldUI_->GetHPpt(player_.GetHP());
		hpShieldUI_->GetShieldpt(player_.GetShield());
		hpShieldUI_->Update();
		bufUI_->Update();
	}
}

void GameFlow::Draw(){
	if (lesson_->GetIsLessonEnd() == true) {
		player_.DrawStatus();
	}else {
		lesson_->Draw();
		hpShieldUI_->Draw();
		bufUI_->Draw();
	}
}

void GameFlow::ApplyGlobalVariables()
{
}
