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

}

StageSelectScene::~StageSelectScene() {
	LightGroup::GetInstance()->ClearCircleShadow();
}

// 更新
void StageSelectScene::Update() {
	gameCamera_->Update();
	select_->Update();
	StateTransition();
}

void StageSelectScene::ObjectDraw() {

}

void StageSelectScene::FbxDraw() {
}

void StageSelectScene::SpriteDraw() {
	select_->Draw();
}

void StageSelectScene::StateTransition() {
	if (Input::GetInstance()->TriggerKey(DIK_1)) {
		sceneManager_->TransitionTo(SceneManager::SCENE::GAME);
	}else if (Input::GetInstance()->TriggerKey(DIK_2)) {
		sceneManager_->TransitionTo(SceneManager::SCENE::GAME);
	}
}