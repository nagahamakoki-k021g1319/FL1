#include "GameFlow.h"
#include"Input.h"

void GameFlow::Initialize(){
	player_.Initilize();

	lesson_ = std::make_unique<Lesson>();
	lesson_->SetPlayer(&player_);
	lesson_->Initialize(6, 60, 2);

	finalTest_ = std::make_unique<FinalTest>();
	finalTest_->SetPlayer(&player_);
	finalTest_->Initialize();
	
	isEndSchedule_ = false;
	isFinalTest_ = false;
	isFirstPick_ = true;

	scheduleCount_ = 0;
	schedule_[0] = 0;
	schedule_[1] = 0;
	schedule_[2] = 1;
	schedule_[3] = 2;
	schedule_[4] = 3;
	schedule_[5] = 4;


	perfectScore[0] = 60;
	perfectScore[1] = 110;
	perfectScore[2] = 120;
	perfectScore[3] = 150;

	spPerfectScore[0] = 90;
	spPerfectScore[1] = 170;
	spPerfectScore[2] = 200;
	spPerfectScore[3] = 220;

	isSp_[0] = false;
	isSp_[1] = false;
	isSp_[2] = false;

	voButton_ = std::make_unique<Button>();
	voButton_->Initialize("selectVo", { 550,500 });
	daButton_ = std::make_unique<Button>();
	daButton_->Initialize("selectDa", { 700,500 });
	viButton_ = std::make_unique<Button>();
	viButton_->Initialize("selectVi", { 850,500 });
	retire_ = std::make_unique<Button>();
	retire_->Initialize("retire", { 1200,30 });
	
	bgmStart_ = false;
	//スケジュール選択画面BGMサウンド鳴らす
	audio_ = new Audio();
	audio_->Initialize();
	audio_->LoadWave("lessonSelectionBGM.wav");

	pSourceVoice_ = audio_->PlayWave("lessonSelectionBGM.wav");


	schedulePng_ = std::make_unique<Sprite>();
	schedulePng_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("schedule.png"));
	schedulePng_->SetSize({ 300,450 });
	schedulePng_->SetPozition({ 60, 135 });
	schedulePng_->Update();

	//selectBackGround_ = std::make_unique<Sprite>();
	//selectBackGround_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("backGround.png"));
	//selectBackGround_->Update();

	spPng_[0] = std::make_unique<Sprite>();
	spPng_[0]->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("SP.png"));
	spPng_[0]->SetPozition({ 510, 460});
	spPng_[0]->Update();
	spPng_[1] = std::make_unique<Sprite>();
	spPng_[1]->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("SP.png"));
	spPng_[1]->SetPozition({ 660, 460 });
	spPng_[1]->Update();
	spPng_[2] = std::make_unique<Sprite>();
	spPng_[2]->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("SP.png"));
	spPng_[2]->SetPozition({ 810, 460 });
	spPng_[2]->Update();

	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		selectBlack_[i][j] = std::make_unique<Sprite>();
	//		selectBlack_[i][j]->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("selectBlack.png"));
	//		selectBlack_[i][j]->SetPozition({ 130.0f + 72.0f * j,515.0f - 64.0f * i});
	//		selectBlack_[i][j]->Update();
	//	}
	//	selectedSchedule_[i] = -1;
	//}
}

void GameFlow::Update(){
	//if (isBGMStart == false) {
	//	pSourceVoice_ = audio_->PlayWave("lessonSelectionBGM.wav");
	//	isBGMStart = true;
	//}
	if (lesson_->GetIsLessonEnd() == false && isFirstPick_ == false) {
		lesson_->Update();
		for (int i = 0; i < 3; i++) {
			if (rand() % 100 <= 45) {
				isSp_[i] = true;
			}else {
				isSp_[i] = false;
			}
		}
	}else if ((lesson_->GetIsLessonEnd() == true && isFinalTest_ == false) || isFirstPick_ == true) {
		if (bgmStart_ == true) {
			//スケジュール選択画面BGMサウンド鳴らす
			pSourceVoice_ = audio_->PlayWave("lessonSelectionBGM.wav");
			bgmStart_ = false;
		}

		if (scheduleCount_ < scheduleNum_) {
			if (schedule_[scheduleCount_] == 0 || schedule_[scheduleCount_] == 1|| schedule_[scheduleCount_] == 2|| schedule_[scheduleCount_] == 3) {
				voButton_->Update();
				daButton_->Update();
				viButton_->Update();
				retire_->Update();
				if (voButton_->IsMouseClick()) {
					if (isSp_[0] == true) {
						lesson_->Initialize(6, spPerfectScore[schedule_[scheduleCount_]], 0);
					}else {
						lesson_->Initialize(6, perfectScore[schedule_[scheduleCount_]], 0);
					}
					player_.DeckReset();
					player_.ScoreReset();
					//selectedSchedule_[scheduleCount_] = 0;
					scheduleCount_++;
					isFirstPick_ = false;
					bgmStart_ = true;
					//スケジュール選択画面BGMサウンド止める
					audio_->StopWave(pSourceVoice_);
				}else if (daButton_->IsMouseClick()) {
					if (isSp_[1] == true) {
						lesson_->Initialize(6, spPerfectScore[schedule_[scheduleCount_]], 1);
					}else {
						lesson_->Initialize(6, perfectScore[schedule_[scheduleCount_]], 1);
					}
					player_.DeckReset();
					player_.ScoreReset();
					//selectedSchedule_[scheduleCount_] = 1;
					scheduleCount_++;
					isFirstPick_ = false;
					bgmStart_ = true;
					//スケジュール選択画面BGMサウンド止める
					audio_->StopWave(pSourceVoice_);
				}else if (viButton_->IsMouseClick()) {
					if (isSp_[2] == true) {
						lesson_->Initialize(6, spPerfectScore[schedule_[scheduleCount_]], 2);
					}else {
						lesson_->Initialize(6, perfectScore[schedule_[scheduleCount_]], 2);
					}
					player_.DeckReset();
					player_.ScoreReset();
					//selectedSchedule_[scheduleCount_] = 2;
					scheduleCount_++;
					isFirstPick_ = false;
					bgmStart_ = true;
					//スケジュール選択画面BGMサウンド止める
					audio_->StopWave(pSourceVoice_);
				}
			}
		}
	}else if (isFinalTest_ == true) {
		finalTest_->Update();
		if (finalTest_->GetIsLessonEnd() == true) {
			isEndSchedule_ = true;
		}
	}

	if (lesson_->GetIsLessonEnd() == true && isFinalTest_ == false) {
		if (schedule_[scheduleCount_] == 4) {
			finalTest_->Initialize();
			isFinalTest_ = true;
			player_.DeckReset();
			player_.ScoreReset();
			scheduleCount_++;
			player_.Heal(20);
		}
	}
}

void GameFlow::Draw(){
	if (lesson_->GetIsLessonEnd() == false && isFirstPick_ == false) {
		lesson_->Draw();
	}else if ((lesson_->GetIsLessonEnd() == true && isFinalTest_ == false) || isFirstPick_ == true) {
		//selectBackGround_->Draw();
		schedulePng_->Draw();
		//for (int i = 0; i < 4; i++) {
		//	if (i < scheduleCount_) {
		//		for (int j = 0; j < 3; j++) {
		//			if (j != selectedSchedule_[i]) {
		//				selectBlack_[i][j]->Draw();
		//			}
		//		}
		//	}
		//}
		player_.DrawStatus();
		voButton_->Draw();
		daButton_->Draw();
		viButton_->Draw();
		retire_->Draw();
		if (isSp_[0]) {
			spPng_[0]->Draw();
		}
		if (isSp_[1]) {
			spPng_[1]->Draw();
		}
		if (isSp_[2]) {
			spPng_[2]->Draw();
		}
	}else if (isFinalTest_ == true) {
		finalTest_->Draw();
	}
}

void GameFlow::ApplyGlobalVariables()
{
}


bool GameFlow::IsRetire(){
	if (retire_->IsMouseClick() == true) {
		audio_->StopWave(pSourceVoice_);
		return true;
	}
	return false;
}