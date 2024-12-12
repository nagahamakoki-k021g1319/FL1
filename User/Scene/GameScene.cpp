/**
 * @file GameScene.cpp
 * @brief ゲームプレイシーン
 */

#include "GameScene.h"
#include "SceneManager.h"
#include "FBXObject3d.h"
#include "FbxLoader.h"
#include "ObjLoader.h"
#include "Model.h"
#include "Object3D.h"
#include "ParticleManager.h"
#include "LightGroup.h"
#include "SpriteLoader.h"

GameScene::GameScene() {}

// 初期化
void GameScene::Initialize() {
	// カメラ生成
	gameCamera_ = make_unique<GameCamera>();
	gameCamera_->Initialize(WinApp::window_width, WinApp::window_height);

	// カメラセット
	FBXObject3d::SetCamera(gameCamera_.get());
	Object3d::SetCamera(gameCamera_.get());
	ParticleManager::SetCamera(gameCamera_.get());

	gameManager_ = std::make_unique<GameManager>();
	gameManager_->Init();

	player_ = make_unique<Player>();
	player_->Initilize();
	gameFlow_ = std::make_unique<GameFlow>();
	gameFlow_->Initialize();
}

GameScene::~GameScene() {
	LightGroup::GetInstance()->ClearCircleShadow();
}

// 更新
void GameScene::Update() {
	gameCamera_->Update();
	gameFlow_->Update();
	player_->Update();

	StateTransition();
}

void GameScene::ObjectDraw() {
	gameFlow_->Draw();

}

void GameScene::FbxDraw() {

}

void GameScene::SpriteDraw() {
	player_->Draw();
}

void GameScene::StateTransition() {
	if (Input::GetInstance()->TriggerKey(DIK_T)) {
		sceneManager_->TransitionTo(SceneManager::SCENE::TITLE);
	}
}