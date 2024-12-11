#include"Player.h"
#include"Input.h"

void Player::Initilize() {
	scoreSprite_ = std::make_unique<Sprite>();
	scoreSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("score.png"));
	scoreSprite_->SetPozition({ 0,0 });
	scoreSprite_->Update();

	hpSprite_ = std::make_unique<Sprite>();
	hpSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("hp.png"));
	hpSprite_->SetPozition({ 0,130 });
	hpSprite_->Update();
	
	shieldSprite_ = std::make_unique<Sprite>();
	shieldSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("shield.png"));
	shieldSprite_->SetPozition({ 120,130 });
	shieldSprite_->Update();
	
	concentrationSprite_ = std::make_unique<Sprite>();
	concentrationSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("concentration.png"));
	concentrationSprite_->SetPozition({ 0,260 });
	concentrationSprite_->Update();
	
	conditionSprite_ = std::make_unique<Sprite>();
	conditionSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("condition.png"));
	conditionSprite_->SetPozition({ 0,390 });
	conditionSprite_->Update();

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

	scoreSprite_->Draw();
	scoreNumber_->Draw({ 0,64 }, score_, 0.8f);
	
	hpSprite_->Draw();
	hpNumber_->Draw({ 0,194 }, hp_, 0.8f);
	
	shieldSprite_->Draw();
	shieldNumber_->Draw({ 120,194 }, shield_, 0.8f);
	
	concentrationSprite_->Draw();
	concentrationNumber_->Draw({ 0,324 }, concentration_, 0.8f);
	
	conditionSprite_->Draw();
	conditionNumber_->Draw({ 0, 454 }, condition_, 0.8f);
}