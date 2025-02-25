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
	remainingTurnPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("finalremainingTurn.png"));
	remainingTurnPing_->SetPozition({ 411,15 });
	remainingTurnPing_->SetSize({ 350.0f / 3.0f,590.0f / 3.0f });
	remainingTurnPing_->Update();

	turnSchedulePing_ = std::make_unique<Sprite>();
	turnSchedulePing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("finalTestSchedule.png"));
	turnSchedulePing_->SetPozition({ 471,97 });
	turnSchedulePing_->Update();
	
	arrowPing_ = std::make_unique<Sprite>();
	arrowPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("arrow.png"));
	arrowPing_->SetPozition({ 459,95 });
	arrowPing_->Update();

	turnNumber_ = std::make_unique<Number>();
	turnNumber_->Initialize();

	explanationPing_ = std::make_unique<Sprite>();
	explanationPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("explanation1.png"));
	explanationPing_->Update();

	hpShieldUI_ = make_unique<HpShieldUI>();
	//bufUI_ = make_unique<BufUI>();
	//bufUI_->Initialize();

	hpShieldUI_->GetHPpt(player_->GetHP());
	hpShieldUI_->GetShieldpt(player_->GetShield());
	hpShieldUI_->Initialize();

	evaluationValueNumber_ = std::make_unique<Number>();
	evaluationValueNumber_->Initialize();

	clearRankPing_ = std::make_unique<Sprite>();
	clearRankPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("clearRank.png"));
	clearRankPing_->SetTexLeftTop({ 0.0f,0.0f });
	clearRankPing_->SetSize({ 256,256 });
	clearRankPing_->SetPozition({ 640,250 });
	clearRankPing_->Update();

	voPercentPing_ = std::make_unique<Sprite>();
	voPercentPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("percent.png"));
	voPercentPing_->SetPozition({ 320,160 });
	voPercentPing_->Update();

	daPercentPing_ = std::make_unique<Sprite>();
	daPercentPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("percent.png"));
	daPercentPing_->SetPozition({ 320,220 });
	daPercentPing_->Update();

	viPercentPing_ = std::make_unique<Sprite>();
	viPercentPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("percent.png"));
	viPercentPing_->SetPozition({ 320,280 });
	viPercentPing_->Update();



	voPercentBackPing_ = std::make_unique<Sprite>();
	voPercentBackPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("voPercentBack.png"));
	voPercentBackPing_->SetPozition({ 230,135 });
	voPercentBackPing_->Update();

	daPercentBackPing_ = std::make_unique<Sprite>();
	daPercentBackPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("daPercentBack.png"));
	daPercentBackPing_->SetPozition({ 230,195 });
	daPercentBackPing_->Update();

	viPercentBackPing_ = std::make_unique<Sprite>();
	viPercentBackPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("viPercentBack.png"));
	viPercentBackPing_->SetPozition({ 230,255 });
	viPercentBackPing_->Update();



	voPercentBlackPing_ = std::make_unique<Sprite>();
	voPercentBlackPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("percentBlack.png"));
	voPercentBlackPing_->SetPozition({ 230,135 });
	voPercentBlackPing_->Update();

	daPercentBlackPing_ = std::make_unique<Sprite>();
	daPercentBlackPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("percentBlack.png"));
	daPercentBlackPing_->SetPozition({ 230,195 });
	daPercentBlackPing_->Update();

	viPercentBlackPing_ = std::make_unique<Sprite>();
	viPercentBlackPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("percentBlack.png"));
	viPercentBlackPing_->SetPozition({ 230,255 });
	viPercentBlackPing_->Update();


	clearPing_ = std::make_unique<Sprite>();
	clearPing_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("end.png"));


	//最終試験BGMサウンド鳴らす
	audio_ = new Audio();
	audio_->Initialize();
	audio_->LoadWave("lessonBGM.wav");

	audio2_ = new Audio();
	audio2_->Initialize();
	audio2_->LoadWave("lessonFinish.wav");


}

void FinalTest::SetPlayer(Player* player) {
	player_ = player;
}

void FinalTest::Update(){
	if (isBGMStart == false) {
		if (isLoopEnd_==false) {
			pSourceVoice_ = audio_->PlayWave("lessonBGM.wav");
			isBGMStart = true;
		}
	}

	if (isLoopEnd_ == false) {
		
		player_->Update(0,statusRate_[turnType[turn_]]);

		arrowPing_->SetPozition({ 459.0f,96.0f + (static_cast<float>(turn_) * 8.0f) });
		arrowPing_->Update();

		if (player_->IsTurnEnd() == true) {
			turn_++;
		}

		//終了判定
		if (turn_ == maxTurn_) {
			isLoopEnd_ = true;
			player_->AddRandSkillDraw();
			//最終試験BGMサウンド止める
			audio_->StopWave(pSourceVoice_);
			//評価値画面BGMサウンド鳴らす
			pSourceVoice2_ = audio2_->PlayWave("lessonFinish.wav");
		}
	}else {
		Calculation(player_->GetStatus(), player_->GetScore());
		if (Input::GetInstance()->TriggerMouse(0)) {
			isLessonEnd_ = true;
			//評価値画面BGMサウンド止める
			audio2_->StopWave(pSourceVoice2_);
			isBGMStart = false;
		}
	}

	hpShieldUI_->GetHPpt(player_->GetHP());
	hpShieldUI_->GetShieldpt(player_->GetShield());
	hpShieldUI_->Update();
	//bufUI_->Update();
}


void FinalTest::Calculation(Vector3 status, int score) {
	int totalStatePoint = static_cast<int>(floor((CalculationState(static_cast<int>(status.x)) + CalculationState(static_cast<int>(status.y)) + CalculationState(static_cast<int>(status.z)) + 1100) * 2.3f));
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

	clearRankPing_->SetPozition({ 500,170 });
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
		player_->Draw(0,statusRate_[turnType[turn_]]);
		remainingTurnPing_->Draw();
		turnNumber_->Draw({ 450,43 }, maxTurn_ - turn_, 0.5f);
		turnSchedulePing_->Draw();
		arrowPing_->Draw();
		if (isLoopEnd_ == true) {
			player_->DrawAddSkill();
		}
		hpShieldUI_->Draw();
		
		voPercentBackPing_->Draw();
		daPercentBackPing_->Draw();
		viPercentBackPing_->Draw();
		for (int i = 0; i < 3; i++) {
			if (statusRate_[i] * 100.0f < 1000.0f) {
				statusRateNumber_[i]->Draw({ 240.0f, 140.0f + 60.0f * i }, static_cast<size_t>(statusRate_[i] * 100.0f), 0.6f);
			}else {
				statusRateNumber_[i]->Draw({ 220.0f, 140.0f + 60.0f * i }, static_cast<size_t>(statusRate_[i] * 100.0f), 0.6f);
			}
		}
		voPercentPing_->Draw();
		daPercentPing_->Draw();
		viPercentPing_->Draw();
		if (turnType[turn_] != 0) {
			voPercentBlackPing_->Draw();
		}
		if (turnType[turn_] != 1) {
			daPercentBlackPing_->Draw();
		}
		if (turnType[turn_] != 2) {
			viPercentBlackPing_->Draw();
		}
	}else {
		//評価値表示画面
		clearPing_->Draw();
		evaluationValueNumber_->Draw({ 530,470 }, evaluationValue_, 1.0f);
		clearRankPing_->Draw();
	}
}

void FinalTest::ApplyGlobalVariables()
{
}