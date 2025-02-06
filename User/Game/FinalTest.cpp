#include "FinalTest.h"
#include<math.h>
#include"Input.h"

void FinalTest::Initialize(){
	maxTurn_ = 12;
	turn_ = 0;
	//流行をvi da voの順とする
	statusCorrection_ = Vector3(1.01f, 1.08f, 1.21f);
	statusRate_[0] = player_->GetStatus().x * statusCorrection_.x/100;
	statusRate_[1] = player_->GetStatus().y * statusCorrection_.y/100;
	statusRate_[2] = player_->GetStatus().z * statusCorrection_.z/100;
	for (int i = 0; i < 3; i++) {
		statusRateNumber_[i] = std::make_unique<Number>();
		statusRateNumber_[i]->Initialize();
	}
	
	turnType[0] = 2;
	
	turnType[1] = 2;
	turnType[2] = 2;
	turnType[3] = 0;
	turnType[4] = 1;
	turnType[5] = 2;
	turnType[6] = 1;
	turnType[7] = 1;
	turnType[8] = 0;

	turnType[9] = 0;
	turnType[10] = 1;
	turnType[11] = 2;

	isLoopEnd_ = false;
	isLessonEnd_ = false;

	remainingTurnPing_ = std::make_unique<Sprite>();
	remainingTurnPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("remainingTurn.png"));
	remainingTurnPing_->SetPozition({ 426,0 });
	remainingTurnPing_->SetSize({ 106,21 });
	remainingTurnPing_->Update();

	turnNumber_ = std::make_unique<Number>();
	turnNumber_->Initialize();

	explanationPing_ = std::make_unique<Sprite>();
	explanationPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("explanation1.png"));
	explanationPing_->Update();

	hpShieldUI_ = make_unique<HpShieldUI>();
	bufUI_ = make_unique<BufUI>();
	bufUI_->Initialize();

	hpShieldUI_->GetHPpt(player_->GetHP());
	hpShieldUI_->GetShieldpt(player_->GetShield());
	hpShieldUI_->Initialize();

	evaluationValueNumber_ = std::make_unique<Number>();
	evaluationValueNumber_->Initialize();

	clearRankPing_ = std::make_unique<Sprite>();
	clearRankPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("clearRank.png"));
	clearRankPing_->SetTexLeftTop({ 0.0f,0.0f });
	clearRankPing_->SetSize({ 256,256 });
	clearRankPing_->SetPozition({ 0,300 });
	clearRankPing_->Update();
}

void FinalTest::SetPlayer(Player* player) {
	player_ = player;
}

void FinalTest::Update(){
	if (isLoopEnd_ == false) {
		
		player_->Update(statusRate_[turnType[turn_]]);

		if (player_->IsTurnEnd() == true) {
			turn_++;
		}

		//終了判定
		if (turn_ == maxTurn_) {
			isLoopEnd_ = true;
			player_->AddRandSkillDraw();
			player_->AddStatus(player_->GetScore(), type_);
		}
	}else {
		Calculation(player_->GetStatus(), player_->GetScore());
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			isLessonEnd_ = true;
		}
	}

	hpShieldUI_->GetHPpt(player_->GetHP());
	hpShieldUI_->GetShieldpt(player_->GetShield());
	hpShieldUI_->Update();
	bufUI_->Update();
}


void FinalTest::Calculation(Vector3 status, int score) {
    int totalStatePoint = static_cast<int>(floor((CalculationState(static_cast<int>(status.x)) + CalculationState(static_cast<int>(status.y)) + CalculationState(static_cast<int>(status.z))) * 2.3f));
    int scorePoint = CalculationRequiredScore(score);
	int totalPoint = totalStatePoint + scorePoint + 1700;
	evaluationValue_ = totalPoint;

    if (totalPoint >= border[6]) {
		clearRank_ = 6;
    }else if (totalPoint >= border[5]) {
		clearRank_ = 5;
    }else if (totalPoint >= border[4]) {
		clearRank_ = 4;
    }else if (totalPoint >= border[3]) {
		clearRank_ = 3;
    }else if (totalPoint >= border[2]) {
		clearRank_ = 2;
	}else if (totalPoint >= border[1]) {
		clearRank_ = 1;
	}else if (totalPoint >= border[0]) {
		clearRank_ = 0;
	}

	clearRankPing_->SetPozition({ 0,300 });
	clearRankPing_->SetTexLeftTop({ 256.f * static_cast<float>(clearRank_) ,0.0f });
	clearRankPing_->SetTexSize({ 256,256 });
	clearRankPing_->Update();
}

int FinalTest::CalculationState(int num) {
	int result;
	if (num <= 1770) {
		result = num + 30;
	}else {
		result = 1800;
	}
	return result;
}

int FinalTest::CalculationRequiredScore(int score) {
	float result = 0;
	float point = static_cast<float>(score);
	if (point <= pointSeparator[0]) {
		result += point * 0.3f;
	}else if (point <= pointSeparator[1]) {
		result += pointSeparator[0] * 0.3f;
		result += (point - pointSeparator[0]) * 0.15f;
	}else if (point <= pointSeparator[2]) {
		result += pointSeparator[0] * 0.3f;
		result += (pointSeparator[1] - pointSeparator[0]) * 0.15f;
		result += (point - pointSeparator[1]) * 0.08f;
	}else if (point <= pointSeparator[3]) {
		result += pointSeparator[0] * 0.3f;
		result += (pointSeparator[1] - pointSeparator[0]) * 0.15f;
		result += (pointSeparator[2] - pointSeparator[1]) * 0.08f;
		result += (point - pointSeparator[2]) * 0.04f;
	}
	else if (point <= pointSeparator[4]) {
		result += pointSeparator[0] * 0.3f;
		result += (pointSeparator[1] - pointSeparator[0]) * 0.15f;
		result += (pointSeparator[2] - pointSeparator[1]) * 0.08f;
		result += (pointSeparator[3] - pointSeparator[2]) * 0.04f;
		result += (point - pointSeparator[3]) * 0.02f;
	}else{
		result += pointSeparator[0] * 0.3f;
		result += (pointSeparator[1] - pointSeparator[0]) * 0.15f;
		result += (pointSeparator[2] - pointSeparator[1]) * 0.08f;
		result += (pointSeparator[3] - pointSeparator[2]) * 0.04f;
		result += (pointSeparator[4] - pointSeparator[3]) * 0.02f;
		result += (point - pointSeparator[4]) * 0.01f;
	}
    return static_cast<int>(result);
}

void FinalTest::Draw() {
	if (isLoopEnd_ == false) {
		explanationPing_->Draw();
		player_->Draw(statusRate_[turnType[turn_]]);
		remainingTurnPing_->Draw();
		turnNumber_->Draw({ 466,21 }, maxTurn_ - turn_, 0.4f);
		if (isLoopEnd_ == true) {
			player_->DrawAddSkill();
		}
		hpShieldUI_->Draw();
		bufUI_->Draw();
		for (int i = 0; i < 3; i++) {
			statusRateNumber_[i]->Draw({ 0.0f, 60.0f*i },static_cast<size_t>(statusRate_[i] * 100.0f), 0.6f);
		}
	}else {
		//評価値表示画面
		evaluationValueNumber_->Draw({ 0,0 }, evaluationValue_, 1.0f);
		clearRankPing_->Draw();
	}
}

void FinalTest::ApplyGlobalVariables()
{
}