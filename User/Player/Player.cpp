#include"Player.h"
#include"Input.h"

void Player::Initilize() {
	scoreSprite_ = std::make_unique<Sprite>();
	scoreSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("score.png"));
	scoreSprite_->SetPozition({ 0,0 });
	scoreSprite_->Update();
	scorePlusSprite_ = std::make_unique<Sprite>();
	scorePlusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("plus.png"));
	scorePlusSprite_->SetPozition({ 118,64 });
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
	concentrationSprite_->SetPozition({ 0,260 });
	concentrationSprite_->Update();
	concentrationPlusSprite_ = std::make_unique<Sprite>();
	concentrationPlusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("plus.png"));
	concentrationPlusSprite_->SetPozition({ 68,324 });
	concentrationPlusSprite_->Update();
	
	conditionSprite_ = std::make_unique<Sprite>();
	conditionSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("condition.png"));
	conditionSprite_->SetPozition({ 0,390 });
	conditionSprite_->Update();
	conditionPlusSprite_ = std::make_unique<Sprite>();
	conditionPlusSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("plus.png"));
	conditionPlusSprite_->SetPozition({ 68,454 });
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

	scoreData_.score = 0;
	maxHp_ = 40;
	hp_ = maxHp_;
	scoreData_.shield = 0;

	changeScore_ = 0;
	changeHp_ = 0;
	changeShield_ = 0;
	changeConcentration_ = 0;
	changeCondition_ = 0;

	skills_.Initilize();
	deck_ = make_unique<Deck>();
	deck_->Initilize(skills_);

	deck_->DrawSkill();
}

void Player::Update() {
	
	//スキル使用後予想
	if (deck_->IsSelectedSkill()) {

		changeScore_ = 0;
		changeHp_ = 0;
		changeShield_ = 0;
		changeConcentration_ = 0;
		changeCondition_ = 0;

		ScoreData scoredata = deck_->GetSelectedSkill().GetScoreData();

		//体力計算
		if (scoreData_.shield >= scoredata.cost) {
			changeShield_ = -scoredata.cost;
		}else {
			changeShield_ = -scoreData_.shield;
			scoredata.cost -= scoreData_.shield;
			changeHp_ = scoredata.cost;
		}

		//スコア計算
		if (scoredata.score > 0) {
			if (scoreData_.condition > 0) {
				float addScore = static_cast<float>(scoredata.score + scoreData_.concentration) * 1.5f;
				changeScore_ = ceil(addScore);
			}
			else {
				changeScore_ = scoredata.score + scoreData_.concentration;
			}
		}

		//バフ追加
		changeConcentration_ = scoredata.concentration;
		changeCondition_ = scoredata.condition;
		changeShield_ += scoredata.shield;
	}

	deck_->Update(&scoreData_, &hp_);
}

void Player::Draw() {
	deck_->DrawHand();
	deck_->DrawList();

	scoreSprite_->Draw();
	scoreNumber_->Draw({ 0,64 }, scoreData_.score, 0.8f);
	
	hpSprite_->Draw();
	hpNumber_->Draw({ 0,194 }, hp_, 0.8f);
	
	shieldSprite_->Draw();
	shieldNumber_->Draw({ 220,194 }, scoreData_.shield, 0.8f);
	
	concentrationSprite_->Draw();
	concentrationNumber_->Draw({ 0,324 }, scoreData_.concentration, 0.8f);
	
	conditionSprite_->Draw();
	conditionNumber_->Draw({ 0, 454 }, scoreData_.condition, 0.8f);

	if (deck_->IsSelectedSkill()) {
		if (changeScore_ != 0) {
			changeScoreNumber_->Draw({ 150,64 }, changeScore_, 0.8f);
			scorePlusSprite_->Draw();
		}
		if (changeHp_ != 0) {
			changeHpNumber_->Draw({ 100,194 }, changeHp_, 0.8f);
			hpMinusSprite_->Draw();
		}
		if (changeShield_ > 0) {
			shieldPlusSprite_->Draw();
			changeShieldNumber_->Draw({ 320,194 }, changeShield_, 0.8f);
		}else if (changeShield_ < 0) {
			changeShieldNumber_->Draw({ 320,194 }, -changeShield_, 0.8f);
			shieldMinusSprite_->Draw();
		}
		if (changeConcentration_ != 0) {
			changeConcentrationNumber_->Draw({ 100,324 }, changeConcentration_, 0.8f);
			concentrationPlusSprite_->Draw();
		}
		if (changeCondition_ != 0) {
			changeConditionNumber_->Draw({ 100, 454 }, changeCondition_, 0.8f);
			conditionPlusSprite_->Draw();
		}
	}
}