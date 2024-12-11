#include"Player.h"
#include"Input.h"

void Player::Initilize() {
	scoreNumber_ = std::make_unique<Number>();
	scoreNumber_->Initialize();
	hpNumber_ = std::make_unique<Number>();
	hpNumber_->Initialize();
	shieldNumber_ = std::make_unique<Number>();
	shieldNumber_->Initialize();
	conditionNumber_ = std::make_unique<Number>();
	conditionNumber_->Initialize();
	concentrationNumber_ = std::make_unique<Number>();
	concentrationNumber_->Initialize();

	score_ = 0;
	hp_ = 40;
	shield_ = 0;

	skills_.Initilize();
	deck_ = make_unique<Deck>();
	deck_->Initilize(skills_);

	deck_->DrawSkill();
}

void Player::Update() {
	deck_->UseSkill();
	
	//スキル使用計算
	if (deck_->IsUsedSkill()) {
		ScoreData scoredata = deck_->GetUsedSkil().GetScoreData();

		//体力計算
		if (shield_ >= scoredata.cost_) {
			shield_ -= scoredata.cost_;
		}else {
			scoredata.cost_ -= shield_;
			shield_ = 0;
			hp_ -= scoredata.cost_;
		}

		//スコア計算
		if (scoredata.score_ > 0) {
			if (condition_ > 0) {
				float addScore = static_cast<float>(scoredata.score_ + concentration_) * 1.5f;
				score_ += ceil(addScore);
			}else {
				score_ += scoredata.score_ + concentration_;
			}
		}

		//バフ追加
		concentration_ += scoredata.concentration_;
		if (condition_ == 0) {
			condition_ += scoredata.condition_;
		}
		else if (condition_ > 0) {
			condition_ += scoredata.condition_;
			condition_--;
		}
		shield_ += scoredata.shield_;

		//ドロー
		deck_->DrawSkill();
	}

	deck_->SpriteSort();
}

void Player::Draw() {
	deck_->DrawHand();
	deck_->DrawList();

	scoreNumber_->Draw({ 0,0 }, score_, 0.8f);
	hpNumber_->Draw({ 0,80 }, hp_, 0.8f);
	shieldNumber_->Draw({ 80,80 }, shield_, 0.8f);
	concentrationNumber_->Draw({ 0,160 }, concentration_, 0.8f);
	conditionNumber_->Draw({ 0,240 }, condition_, 0.8f);
}