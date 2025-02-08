#include "Lesson.h"

void Lesson::Initialize(int maxTurn, int perfectScore,int type) {
	maxTurn_ = maxTurn;
	turn_ = 0;
	clearScore_ = perfectScore / 2;
	perfectScore_ = perfectScore;
	isLoopEnd_ = false;
	isLessonEnd_ = false;

	remainingTurnPing_ = std::make_unique<Sprite>();
	remainingTurnPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("remainingTurn.png"));
	remainingTurnPing_->SetPozition({ 411,15 });
	remainingTurnPing_->SetSize({ 350.0f / 3.0f,200.0f / 3.0f });
	remainingTurnPing_->Update();

	turnNumber_ = std::make_unique<Number>();
	turnNumber_->Initialize();


	borderScoreNumber_ = std::make_unique<Number>();
	borderScoreNumber_->Initialize();

	clearScorePing_ = std::make_unique<Sprite>();
	clearScorePing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("clearScore.png"));
	clearScorePing_->SetPozition({ 810 - (400 / 3 / 2), 15 });
	clearScorePing_->Update();

	perfectScorePing_ = std::make_unique<Sprite>();
	perfectScorePing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("perfectScore.png"));
	perfectScorePing_->SetPozition({ 810 - (400 / 3 / 2), 15 });
	perfectScorePing_->Update();
	
	explanationPing_ = std::make_unique<Sprite>();
	explanationPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("explanation1.png"));
	explanationPing_->Update();

	type_ = type;

	hpShieldUI_ = make_unique<HpShieldUI>();
	bufUI_ = make_unique<BufUI>();
	bufUI_->Initialize();

	hpShieldUI_->GetHPpt(player_->GetHP());
	hpShieldUI_->GetShieldpt(player_->GetShield());
	hpShieldUI_->Initialize();

	//レッスン中bgmサウンド鳴らす
}

void Lesson::SetPlayer(Player* player){
	player_ = player;
}

void Lesson::Update() {
	if (isLoopEnd_ == false) {
		player_->Update(perfectScore_);
		if (player_->IsTurnEnd() == true) {
			turn_++;
		}

		//終了判定
		if (turn_ == maxTurn_) {
			isLoopEnd_ = true;
			if (player_->GetScore() >= clearScore_) {
				player_->AddRandSkillDraw();
			}
			player_->AddStatus(player_->GetScore(), type_);
		}
		if (player_->GetScore() >= perfectScore_) {
			isLoopEnd_ = true;
			player_->AddRandSkillDraw();
			player_->AddStatus(player_->GetScore(),type_);
		}
	}
	else {
		if (player_->GetScore() >= clearScore_) {
			player_->AddRandSkillReload();
			if (player_->addRandSkill()) {
				isLessonEnd_ = true;
				//レッスン中bgmサウンド止める
			}
		}else {
			isLessonEnd_ = true;
			//レッスン中bgmサウンド止める
		}
	}

	hpShieldUI_->GetHPpt(player_->GetHP());
	hpShieldUI_->GetShieldpt(player_->GetShield());
	hpShieldUI_->Update();
	bufUI_->Update();
}

void Lesson::Draw() {
	explanationPing_->Draw();
	player_->Draw(perfectScore_);
	remainingTurnPing_->Draw();
	turnNumber_->Draw({ 450,43 }, maxTurn_ - turn_, 0.5f);

	if (player_->GetScore() < clearScore_) {
		clearScorePing_->Draw();
		borderScoreNumber_->Draw({ 780,40 }, clearScore_ - player_->GetScore(), 0.4f);
	}else {
		perfectScorePing_->Draw();
		borderScoreNumber_->Draw({ 780,40 }, perfectScore_ - player_->GetScore(), 0.4f);
	}

	if (isLoopEnd_ == true) {
		if (player_->GetScore() >= clearScore_) {
			player_->DrawAddSkill();
		}
	}
	hpShieldUI_->Draw();
	bufUI_->Draw();
}