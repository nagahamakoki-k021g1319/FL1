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


	skills_.Initilize();
	deck_ = make_unique<Deck>();
	deck_->Initilize(skills_);
}

GameScene::~GameScene() {
	LightGroup::GetInstance()->ClearCircleShadow();
}

// 更新
void GameScene::Update() {
	gameCamera_->Update();


	if (Input::GetInstance()->TriggerKey(DIK_A)) {
		deck_->DrawSkill();
	}else if (Input::GetInstance()->TriggerKey(DIK_S)) {
		deck_->UseSkill();
	}else if (Input::GetInstance()->TriggerKey(DIK_D)) {
		deck_->Discard();
	}

	StateTransition();
}

void GameScene::ObjectDraw() {


}

void GameScene::FbxDraw() {

}

void GameScene::SpriteDraw() {
	deck_->DrawHand();
}

void GameScene::StateTransition() {
	if (Input::GetInstance()->TriggerKey(DIK_T)) {
		sceneManager_->TransitionTo(SceneManager::SCENE::TITLE);
	}
}