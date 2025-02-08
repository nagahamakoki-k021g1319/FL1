/**
 * @file TitelScene.cpp
 * @brief タイトルシーン
 */
#include"TitleScene.h"
#include"SceneManager.h"

#include"FbxLoader.h"
#include"SpriteLoader.h"
#include"LightGroup.h"
#include <imgui.h>

TitleScene::TitleScene() {}

// 初期化
void TitleScene::Initialize() {
	// カメラ生成
	gameCamera_ = make_unique<GameCamera>();
	gameCamera_->Initialize(WinApp::window_width, WinApp::window_height);
	// カメラセット
	FBXObject3d::SetCamera(gameCamera_.get());
	Object3d::SetCamera(gameCamera_.get());
	ParticleManager::SetCamera(gameCamera_.get());

	title_ = std::make_unique<Sprite>();
	title_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("title.png"));

	titleButton_ = std::make_unique<Button>();
	titleButton_->Initialize("start", { 640,600 });
}

TitleScene::~TitleScene() {
	LightGroup::GetInstance()->ClearCircleShadow();
}

// 更新
void TitleScene::Update() {
	gameCamera_->Update();


	title_->Update();
	titleButton_->Update();
	StateTransition();
}

void TitleScene::ObjectDraw() {
}

void TitleScene::FbxDraw() {
}

void TitleScene::SpriteDraw() {
	title_->Draw();
	titleButton_->Draw();
}

void TitleScene::StateTransition() {
	if (Input::GetInstance()->TriggerMouse(0)) {
		sceneManager_->TransitionTo(SceneManager::SCENE::SELECT);
	}
}