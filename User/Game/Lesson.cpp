#include "Lesson.h"

void Lesson::Initialize(int maxTurn, int clearScore, int perfectScore){
	maxTurn_ = maxTurn;
	turn_ = 0;
	clearScore_ = clearScore;
	perfectScore_ = perfectScore;
	isLessonEnd_ = false;

	remainingTurnPing_ = std::make_unique<Sprite>();
	remainingTurnPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("remainingTurn.png"));
	remainingTurnPing_->SetPozition({ 480,0 });
	remainingTurnPing_->Update();

	turnNumber_ = std::make_unique<Number>();
	turnNumber_->Initialize();

}

void Lesson::Update(){
	player_->Update();

	if (player_->IsTurnEnd() == true) {
		turn_++;
	}
	if (turn_ == maxTurn_) {
		isLessonEnd_ = true;
	}
	if (player_->GetScore() > perfectScore_) {
		isLessonEnd_ = true;
	}
}

void Lesson::Draw(){
	player_->Draw();
	remainingTurnPing_->Draw();
	turnNumber_->Draw({ 640,64 }, maxTurn_ - turn_, 0.8f);
}