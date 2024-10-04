#include "BaseMovie.h"
#include "Easing.h"
#include "SpriteLoader.h"
#include "TGameCamera.h"

BaseMovie::~BaseMovie() {}

void BaseMovie::Init() {
	for (size_t i = 0; i < movieBar_.size(); i++) {
		movieBar_[i] = std::make_unique<Sprite>();
		movieBar_[i]->Initialize(SpriteCommon::GetInstance());
		movieBar_[i]->SetSize({WinApp::window_width, WinApp::window_height / 10.0f});
		movieBar_[i]->SetColor({0, 0, 0, 1});
		movieBar_[i]->SetTextureIndex(SpriteLoader::GetInstance()->GetTextureIndex("white.png"));
	}

	movieBar_[0]->SetAnchorPoint({0, 0});
	movieBar_[1]->SetAnchorPoint({0, 1});
}

void BaseMovie::Update(TGameCamera* camera) {
	MyEngine::Vector3 hoge = camera->GetEye();
	for (size_t i = 0; i < movieBar_.size(); i++) {
		movieBar_[i]->SetPozition(movieBarPos_[i]);
	}
}

void BaseMovie::Draw() {
	if (!isFinish_) {
		for (size_t i = 0; i < movieBar_.size(); i++) {
			movieBar_[i]->Draw();
		}
	}
}

void BaseMovie::MovieBarInInit() {
	float height = static_cast<float>(WinApp::window_height);

	movieBarPos_[0] = {0.0f, 0.0f};
	movieBarPos_[1] = {0.0f, height};
}

void BaseMovie::MovieBarOutInit() {
	float height = static_cast<float>(WinApp::window_height);

	movieBarPos_[0] = {0.0f, -50.0f};
	movieBarPos_[1] = {0.0f, height + 50.0f};
}

void BaseMovie::MovieBarOut(const float timer_) {
	// ムービーバーを上下へ
	float height = static_cast<float>(WinApp::window_height);
	movieBarPos_[0].y = MyEngine::Easing::InQuad(0.0f, -50.0f, timer_);
	movieBarPos_[1].y = MyEngine::Easing::InQuad(height, height + 50.0f, timer_);
}

void BaseMovie::MovieBarIn(const float timer_) {
	// ムービーバーを上下へ
	float height = static_cast<float>(WinApp::window_height);
	movieBarPos_[0].y = MyEngine::Easing::InQuad(-50.0f, 0.0f, timer_);
	movieBarPos_[1].y = MyEngine::Easing::InQuad(height + 50.0f, height, timer_);
}

const bool& BaseMovie::GetIsFinish() const { return isFinish_; }

void BaseMovie::SetIsFinish(bool isFinish) { isFinish_ = isFinish; }
