/**
 * @file GameMain.cpp
 * @brief ゲーム全体の流れ
 */
#include "GameMain.h"

GameMain::GameMain() {}
GameMain::~GameMain() {}

void GameMain::Initialize() {
	Framework::Initialize();
	//シーンの初期化
	sceneManager_ = new SceneManager();
	sceneManager_->Initialize(dxCommon_);
}

void GameMain::Finalize() {
	delete sceneManager_;
	Framework::Finalize();
}

void GameMain::Update() {
	Framework::Update();
	sceneManager_->Update();
}

void GameMain::Draw() {
	Framework::Draw();
	sceneManager_->Draw();
}

bool GameMain::IsEndRequst() {
	return Framework::IsEndRequst();
}