#include"Player.h"
#include"Input.h"

void Player::Initilize() {
	scoreSprite_ = std::make_unique<Sprite>();
	scoreSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("score.png"));
	scoreSprite_->SetAnchorPoint({ 0.5f,0.0f });
	scoreSprite_->SetPozition({ 640,25 });
	scoreSprite_->Update();

	scorePlusSprite_ = std::make_unique<Sprite>();
	scorePlusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("plus.png"));
	scorePlusSprite_->SetPozition({ 640,100 });
	scorePlusSprite_->SetAnchorPoint({ 0.5f,0 });
	scorePlusSprite_->SetSize({32,32});
	scorePlusSprite_->Update();

	hpSprite_ = std::make_unique<Sprite>();
	hpSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("hp.png"));
	hpSprite_->SetPozition({ 0,130 });
	hpSprite_->Update();
	hpMinusSprite_ = std::make_unique<Sprite>();
	hpMinusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("minus.png"));
	hpMinusSprite_->SetPozition({ 155,117 });
	hpMinusSprite_->Update();


	hpChangedFrameSprite_ = std::make_unique<Sprite>();
	hpChangedFrameSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("ChangedFrame.png"));
	hpChangedFrameSprite_->SetPozition({ 155,117 });
	hpChangedFrameSprite_->Update();

	shieldChangedFrameSprite_ = std::make_unique<Sprite>();
	shieldChangedFrameSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("ChangedFrame.png"));
	shieldChangedFrameSprite_->SetPozition({ 247,92 });
	shieldChangedFrameSprite_->Update();
	
	shieldSprite_ = std::make_unique<Sprite>();
	shieldSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("shield.png"));
	shieldSprite_->SetPozition({ 130,130 });
	shieldSprite_->Update();
	shieldMinusSprite_ = std::make_unique<Sprite>();
	shieldMinusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("minus.png"));
	shieldMinusSprite_->SetPozition({ 245,92 });
	shieldMinusSprite_->Update();
	shieldPlusSprite_ = std::make_unique<Sprite>();
	shieldPlusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("plus.png"));
	shieldPlusSprite_->SetPozition({ 245,92 });
	shieldPlusSprite_->Update();
	
	concentrationSprite_ = std::make_unique<Sprite>();
	concentrationSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("concentration.png"));
	concentrationSprite_->SetPozition({ 50,140});
	concentrationSprite_->SetSize({ 32,32 });
	concentrationSprite_->Update();
	concentrationPlusSprite_ = std::make_unique<Sprite>();
	concentrationPlusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("plus.png"));
	concentrationPlusSprite_->SetPozition({ 100,150 });
	concentrationPlusSprite_->SetSize({ 32,32 });
	concentrationPlusSprite_->Update();
	
	conditionSprite_ = std::make_unique<Sprite>();
	conditionSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("condition.png"));
	conditionSprite_->SetPozition({ 50,184});
	conditionSprite_->SetSize({ 32,32 });
	conditionSprite_->Update();
	conditionPlusSprite_ = std::make_unique<Sprite>();
	conditionPlusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("plus.png"));
	conditionPlusSprite_->SetPozition({ 100,194 });
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
	addSelectSprite_->SetPozition({440,320});
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

	status_ = Vector3(200, 230, 250);
	//status_ += Vector3{ 90,180,90 };
	//status_ += Vector3{ 145,310,145 };
}

void Player::Update(int maxScore, float rate) {
	deck_->Update(&scoreData_, &hp_,maxScore, rate);
	if (deck_->IsUsedSkill() == true) {
		isTurnEnd_ = true;
	}
}

void Player::Draw(int maxScore, float rate) {
	deck_->DrawHand();
	deck_->DrawList();

	scoreSprite_->Draw();
	scoreNumber_->Draw({ 605,65 }, scoreData_.score, 0.7f);
	
	concentrationSprite_->Draw();
	concentrationNumber_->Draw({ 74,155 }, scoreData_.concentration, 0.35f);
	
	conditionSprite_->Draw();
	conditionNumber_->Draw({ 74, 199 }, scoreData_.condition, 0.35f);

	if (deck_->IsSelectedSkill()) {
		ScoreData changedScoreData = deck_->GetChangedScoreData(&scoreData_, maxScore, rate);
		int changeHp = deck_->GetChangedHp(&scoreData_);

		if (changedScoreData.score != 0) {
			changeScoreNumber_->Draw({ 615,120 }, changedScoreData.score, 0.4f);
			scorePlusSprite_->Draw();
		}

		if (changeHp != 0) {
			hpChangedFrameSprite_->Draw();
			changeHpNumber_->Draw({ 165,120 }, changeHp, 0.4f);
			hpMinusSprite_->Draw();
		}

		if (changedScoreData.shield > 0) {
			shieldChangedFrameSprite_->Draw();
			shieldPlusSprite_->Draw();
			changeShieldNumber_->Draw({ 257,95 }, changedScoreData.shield, 0.4f);
		}else if (changedScoreData.shield < 0) {
			shieldChangedFrameSprite_->Draw();
			changeShieldNumber_->Draw({ 257,95 }, -changedScoreData.shield, 0.4f);
			shieldMinusSprite_->Draw();
		}

		if (changedScoreData.concentration != 0) {
			changeConcentrationNumber_->Draw({ 114,155 }, changedScoreData.concentration, 0.35f);
			concentrationPlusSprite_->Draw();
		}

		if (changedScoreData.condition != 0) {
			changeConditionNumber_->Draw({ 114, 199 }, changedScoreData.condition, 0.35f);
			conditionPlusSprite_->Draw();
		}
	}
}

void Player::DrawStatus() {
	statusNumber_[0]->Draw({ 490.0f, 400.0f }, static_cast<size_t>(status_.x), 0.8f);
	statusNumber_[1]->Draw({ 640.0f, 400.0f }, static_cast<size_t>(status_.y), 0.8f);
	statusNumber_[2]->Draw({ 790.0f, 400.0f }, static_cast<size_t>(status_.z), 0.8f);
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
	if (type == 0) {
		status_.x += add;
	}else if (type == 1) {
		status_.y += add;
	}else if (type == 2) {
		status_.z += add;
	}
}

void Player::Heal(int healPoint) {
	hp_ += healPoint;
	if (hp_ > maxHp_) {
		hp_ = maxHp_;
	}
}

void Player::AddRandSkillReload() {
	if (deck_->IsReloard()) {
		deck_->AddRandSkillDraw(skills_);
	}
}