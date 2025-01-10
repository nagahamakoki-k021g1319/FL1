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
	remainingTurnPing_->SetPozition({ 426,0 });
	remainingTurnPing_->SetSize({106,21});
	remainingTurnPing_->Update();

	turnNumber_ = std::make_unique<Number>();
	turnNumber_->Initialize();

	explanationPing_ = std::make_unique<Sprite>();
	explanationPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("explanation1.png"));
	explanationPing_->Update();

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
			player_->AddRandSkillDraw();
			player_->AddStatus(player_->GetScore(), type_);
		}
		if (player_->GetScore() > perfectScore_) {
			isLoopEnd_ = true;
			player_->AddRandSkillDraw();
			player_->AddStatus(player_->GetScore(),type_);
		}
	}
	else {
		if (player_->addRandSkill()) {
			isLessonEnd_ = true;
		}
	}

}

void Lesson::Draw() {
	explanationPing_->Draw();
	player_->Draw();
	remainingTurnPing_->Draw();
	turnNumber_->Draw({ 466,21 }, maxTurn_ - turn_, 0.4f);
	if (isLoopEnd_==true) {
		player_->DrawAddSkill();
	}
}