#include "Lesson.h"

void Lesson::Initialize(int maxTurn, int clearScore, int perfectScore,int type) {
	maxTurn_ = maxTurn;
	turn_ = 0;
	clearScore_ = clearScore;
	perfectScore_ = perfectScore;
	isLoopEnd_ = false;
	isLessonEnd_ = false;

	remainingTurnPing_ = std::make_unique<Sprite>();
	remainingTurnPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("remainingTurn.png"));
	remainingTurnPing_->SetPozition({ 480,0 });
	remainingTurnPing_->Update();

	turnNumber_ = std::make_unique<Number>();
	turnNumber_->Initialize();

	type_ = type;
}

void Lesson::Update() {
	if (isLoopEnd_ == false) {
		player_->Update();
		if (player_->IsTurnEnd() == true) {
			turn_++;
		}

		//終了判定
		if (turn_ == maxTurn_) {
			isLoopEnd_ = true;
		}
		if (player_->GetScore() > perfectScore_) {
			isLoopEnd_ = true;
		}
	}else {
		//ステータス上昇
		player_->AddStatus(player_->GetScore(),type_);
		//スキル追加処理追加予定
		//追加したらtrueにする
		isLessonEnd_ = true;
	}

}

void Lesson::Draw() {
	player_->Draw();
	remainingTurnPing_->Draw();
	turnNumber_->Draw({ 640,64 }, maxTurn_ - turn_, 0.8f);
}