#include "GameFlow.h"

void GameFlow::Initialize(){
	player_.Initilize();

	lesson_ = std::make_unique<Lesson>();
	lesson_->Initialize(6, 60, 90);

	lesson_->SetPlayer(&player_);
}

void GameFlow::Update(){
	if (lesson_->GetIsLessonEnd() == true) {
		//内容切替え
		lesson_->Initialize(6, 60, 90);
		player_.DeckReset();
		player_.ScoreReset();
	}else {
		lesson_->Update();
	}
}

void GameFlow::Draw(){
	if (lesson_->GetIsLessonEnd() == true) {
		//内容切替え
	}else {
		lesson_->Draw();
	}
}

void GameFlow::ApplyGlobalVariables()
{
}
