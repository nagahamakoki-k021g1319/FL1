/**
 * @file StageSelectScene.cpp
 * @brief タイトルシーン
 */
#include"StageSelectScene.h"
#include"SceneManager.h"
#include"GameScene.h"

#include"FbxLoader.h"
#include"SpriteLoader.h"
#include"LightGroup.h"

StageSelectScene::StageSelectScene() {}

// 初期化
void StageSelectScene::Initialize() {
	// カメラ生成
	gameCamera_ = make_unique<GameCamera>();
	gameCamera_->Initialize(WinApp::window_width, WinApp::window_height);
	// カメラセット
	FBXObject3d::SetCamera(gameCamera_.get());
	Object3d::SetCamera(gameCamera_.get());
	ParticleManager::SetCamera(gameCamera_.get());

	select_ = std::make_unique<Sprite>();
	select_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("select.png"));

	easyButton_ = std::make_unique<Button>();
	easyButton_->Initialize("easy", { 440,450 });
	normalButton_ = std::make_unique<Button>();
	normalButton_->Initialize("normal", { 840,450 });

	goTitleButton_ = std::make_unique<Button>();
	goTitleButton_->Initialize("goTitle", { 1100,50 });
}

StageSelectScene::~StageSelectScene() {
	LightGroup::GetInstance()->ClearCircleShadow();
}

// 更新
void StageSelectScene::Update() {
	gameCamera_->Update();
	select_->Update();
	easyButton_->Update();
	normalButton_->Update();
	goTitleButton_->Update();
	StateTransition();
}

void StageSelectScene::ObjectDraw() {

}

void StageSelectScene::FbxDraw() {
}

void StageSelectScene::SpriteDraw() {
	select_->Draw();
	easyButton_->Draw();
	normalButton_->Draw();
	goTitleButton_->Draw();
}

void StageSelectScene::StateTransition() {
	if (easyButton_->IsMouseClick()==true) {
		sceneManager_->TransitionTo(SceneManager::SCENE::GAME);
	}
	if (normalButton_->IsMouseClick() == true) {
		sceneManager_->TransitionTo(SceneManager::SCENE::GAME);
	}
	if (goTitleButton_->IsMouseClick() == true) {
		sceneManager_->TransitionTo(SceneManager::SCENE::TITLE);
	}
}