#include"Player.h"
#include"Input.h"

void Player::Initilize() {
	score_ = 0;
	hp_ = 40;
	shield_ = 0;

	skills_.Initilize();
	deck_ = make_unique<Deck>();
	deck_->Initilize(skills_);
}

void Player::Update() {
	if (Input::GetInstance()->TriggerKey(DIK_A)) {
		deck_->DrawSkill();
	}

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
		if (condition_ > 0) {
			float addScore = static_cast<float>(scoredata.score_ + concentration_) * 1.5f;
			score_ += ceil(addScore);
		}else {
			score_ += scoredata.score_ + concentration_;
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
	}

	deck_->SpriteSort();
}

void Player::Draw() {
	deck_->DrawHand();
	deck_->DrawList();
}