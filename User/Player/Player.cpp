#include"Player.h"
#include"Input.h"

void Player::Initilize() {
	scoreSprite_ = std::make_unique<Sprite>();
	scoreSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("score.png"));
	scoreSprite_->SetAnchorPoint({ 0.5f,0.0f });
	scoreSprite_->SetSize({123,48});
	scoreSprite_->SetPozition({ 640,0 });
	scoreSprite_->Update();
	scorePlusSprite_ = std::make_unique<Sprite>();
	scorePlusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("plus.png"));
	scorePlusSprite_->SetPozition({ 640,90 });
	scorePlusSprite_->SetAnchorPoint({ 0.5f,0 });
	scorePlusSprite_->SetSize({32,32});
	scorePlusSprite_->Update();

	hpSprite_ = std::make_unique<Sprite>();
	hpSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("hp.png"));
	hpSprite_->SetPozition({ 0,130 });
	hpSprite_->Update();
	hpMinusSprite_ = std::make_unique<Sprite>();
	hpMinusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("minus.png"));
	hpMinusSprite_->SetPozition({ 68,194 });
	hpMinusSprite_->Update();
	
	shieldSprite_ = std::make_unique<Sprite>();
	shieldSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("shield.png"));
	shieldSprite_->SetPozition({ 130,130 });
	shieldSprite_->Update();
	shieldMinusSprite_ = std::make_unique<Sprite>();
	shieldMinusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("minus.png"));
	shieldMinusSprite_->SetPozition({ 288,194 });
	shieldMinusSprite_->Update();
	shieldPlusSprite_ = std::make_unique<Sprite>();
	shieldPlusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("plus.png"));
	shieldPlusSprite_->SetPozition({ 288,194 });
	shieldPlusSprite_->Update();
	
	concentrationSprite_ = std::make_unique<Sprite>();
	concentrationSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("concentration.png"));
	concentrationSprite_->SetPozition({ 426,70 });
	concentrationSprite_->SetSize({ 32,32 });
	concentrationSprite_->Update();
	concentrationPlusSprite_ = std::make_unique<Sprite>();
	concentrationPlusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("plus.png"));
	concentrationPlusSprite_->SetPozition({ 466,80 });
	concentrationPlusSprite_->SetSize({ 32,32 });
	concentrationPlusSprite_->Update();
	
	conditionSprite_ = std::make_unique<Sprite>();
	conditionSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("condition.png"));
	conditionSprite_->SetPozition({ 426,114 });
	conditionSprite_->SetSize({ 32,32 });
	conditionSprite_->Update();
	conditionPlusSprite_ = std::make_unique<Sprite>();
	conditionPlusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("plus.png"));
	conditionPlusSprite_->SetPozition({ 466,124 });
	conditionPlusSprite_->SetSize({ 32,32 });
	conditionPlusSprite_->Update();


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

	changeScoreNumber_ = std::make_unique<Number>();
	changeScoreNumber_->Initialize();
	changeHpNumber_ = std::make_unique<Number>();
	changeHpNumber_->Initialize();
	changeShieldNumber_ = std::make_unique<Number>();
	changeShieldNumber_->Initialize();
	changeConditionNumber_ = std::make_unique<Number>();
	changeConditionNumber_->Initialize();
	changeConcentrationNumber_ = std::make_unique<Number>();
	changeConcentrationNumber_->Initialize();


	addSelectSprite_ = std::make_unique<Sprite>();
	addSelectSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("addselect.png"));
	addSelectSprite_->SetPozition({425,360});
	addSelectSprite_->Update();

	for (int i = 0; i < 3; i++) {
		statusNumber_[i] = std::make_unique<Number>();
		statusNumber_[i]->Initialize();
	}

	scoreData_.score = 0;
	maxHp_ = 40;
	hp_ = maxHp_;
	scoreData_.shield = 0;

	skills_.Initilize();
	deck_ = make_unique<Deck>();
	deck_->Initilize(skills_);

	deck_->DrawSkill();

	isTurnEnd_ = false;

	status_[0] = 150;
	status_[1] = 150;
	status_[2] = 150;
}

void Player::Update() {
	deck_->Update(&scoreData_, &hp_);
	if (deck_->IsUsedSkill() == true) {
		isTurnEnd_ = true;
	}
}

void Player::Draw() {
	deck_->DrawHand();
	deck_->DrawList();

	scoreSprite_->Draw();
	scoreNumber_->Draw({ 605,48 }, scoreData_.score, 0.8f);
	
	concentrationSprite_->Draw();
	concentrationNumber_->Draw({ 440,85 }, scoreData_.concentration, 0.35f);
	
	conditionSprite_->Draw();
	conditionNumber_->Draw({ 440, 129 }, scoreData_.condition, 0.35f);

	if (deck_->IsSelectedSkill()) {
		ScoreData changedScoreData = deck_->GetChangedScoreData(&scoreData_);
		int changeHp = deck_->GetChangedHp(&scoreData_);

		if (changedScoreData.score != 0) {
			changeScoreNumber_->Draw({ 615,110 }, changedScoreData.score, 0.4f);
			scorePlusSprite_->Draw();
		}

		if (changeHp != 0) {
			changeHpNumber_->Draw({ 100,194 }, changeHp, 0.8f);
			hpMinusSprite_->Draw();
		}

		if (changedScoreData.shield > 0) {
			shieldPlusSprite_->Draw();
			changeShieldNumber_->Draw({ 320,194 }, changedScoreData.shield, 0.8f);
		}else if (changedScoreData.shield < 0) {
			changeShieldNumber_->Draw({ 320,194 }, -changedScoreData.shield, 0.8f);
			shieldMinusSprite_->Draw();
		}

		if (changedScoreData.concentration != 0) {
			changeConcentrationNumber_->Draw({ 480,85 }, changedScoreData.concentration, 0.35f);
			concentrationPlusSprite_->Draw();
		}

		if (changedScoreData.condition != 0) {
			changeConditionNumber_->Draw({ 480, 129 }, changedScoreData.condition, 0.35f);
			conditionPlusSprite_->Draw();
		}
	}
}

void Player::DrawStatus() {
	for (int i = 0; i < 3; i++) {
		statusNumber_[i]->Draw({ 490.0f + (100.0f * static_cast<float>(i)),400.0f }, status_[i], 0.8f);
	}
}

bool Player::IsTurnEnd() {
	if (isTurnEnd_ == true) {
		isTurnEnd_ = false;
		return true;
	}
	return false;
}

void Player::DeckReset() {
	deck_->ResetDeck();
}


void Player::ScoreReset() {
	scoreData_.score = 0;
	scoreData_.shield = 0;
	scoreData_.concentration = 0;
	scoreData_.condition = 0;
}

void Player::AddStatus(int add, int type) {
	status_[type] += add;
}