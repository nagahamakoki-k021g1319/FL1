/**
 * @file SceneState.cpp
 * @brief シーン遷移演出
 */
#include"SceneChange.h"
#include"SpriteLoader.h"

SceneChange::SceneChange(){}

void SceneChange::Initialize() {
	//明転
	isFadeIn = false;
	blackSubtractAlpha = 0.05f;

	//暗転
	isFadeOut = false;
	isFadeOutFin = false;
	blackAddAlpha = 0.04f;

	//画像
	black_ = std::make_unique<Sprite>();
	black_->Initialize(SpriteCommon::GetInstance());
	black_->SetSize({ WinApp::window_width,WinApp::window_height });
	black_->SetColor({ 0,0,0,0 });

	loading_ = std::make_unique<Sprite>();
	loading_->Initialize(SpriteCommon::GetInstance());
	loading_->SetSize({ WinApp::window_width,WinApp::window_height });

	black_->SetTextureIndex(SpriteLoader::GetInstance()->GetTextureIndex("white.png"));
	loading_->SetTextureIndex(SpriteLoader::GetInstance()->GetTextureIndex("loading.png"));
	black_->Update();
	loading_->Update();
}

void SceneChange::Update() {
	FadeIn();
	FadeOut();
	black_->Update();
	loading_->Update();
}

void SceneChange::FadeIn() {
	if (isFadeIn) {
		black_->SetColor({ 0,0,0,black_->GetColor().w - blackSubtractAlpha });
		if (black_->GetColor().w < 0.0f) {
			black_->SetColor({ 0,0,0,0 });
			isFadeIn = false;
		}
	}
}

void SceneChange::FadeOut() {
	if (isFadeOut) {
		black_->SetColor({ 0,0,0,black_->GetColor().w + blackAddAlpha });
		if (black_->GetColor().w > 1.0f) {
			black_->SetColor({ 0,0,0,1.0f });
			isFadeOut = false;
			isFadeOutFin = true;
		}
	}
}

void SceneChange::SpriteDraw() {
	black_->Draw();
	if (black_->GetColor().w >= 1.0f) {
		loading_->Draw();
	}
}

void SceneChange::FadeOutStart() {
	isFadeOut = true;
};

void SceneChange::FadeInStart() {
	isFadeIn = true;
	isFadeOutFin = false;
	isFadeOut = false;
};

bool SceneChange::GetIsFadeOutFin() {
	return isFadeOutFin;
};