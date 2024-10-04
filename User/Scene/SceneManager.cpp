/**
 * @file SceneManager.cpp
 * @brief シーン管理
 */
#include"Object3d.h"
#include"FBXObject3d.h"
#include"SceneManager.h"

#include"TitleScene.h"
#include"StageSelectScene.h"
#include"GameScene.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

void SceneManager::Initialize(DirectXCommon* dxCommon) {
	assert(dxCommon);
	this->dxCommon_ = dxCommon;

	SceneState::SetSceneManager(this);
	state_ = std::make_unique<TitleScene>();
	state_->Initialize();

	sceneChange_ = std::make_unique<SceneChange>();
	sceneChange_->Initialize();
}

void SceneManager::TransitionTo(SCENE nextScene) {
	sceneChange_->FadeOutStart();
	nextScene_ = nextScene;
}

void SceneManager::Update() {
	state_->Update();
	ChangeScene();
	sceneChange_->Update();
}

void SceneManager::Draw() {
	///fbx描画前処理
	FBXObject3d::PreDraw(dxCommon_->GetCommandList());
	///FBX描画
	state_->FbxDraw();
	///FBX描画後処理
	FBXObject3d::PostDraw();

	///3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon_->GetCommandList());
	///3Dオブクジェクトの描画 
	state_->ObjectDraw();
	///3Dオブジェクト描画後処理
	Object3d::PostDraw();

	state_->SpriteDraw();
	sceneChange_->SpriteDraw();
}

void SceneManager::ChangeScene() {
	if (sceneChange_->GetIsFadeOutFin()) {
		//新規作成
		if (nextScene_ == SCENE::TITLE) {
			state_ = std::make_unique<TitleScene>();
		}else if (nextScene_ == SCENE::SELECT) {
			state_ = std::make_unique<StageSelectScene>();
		}else if (nextScene_ == SCENE::GAME) {
			state_ = std::make_unique<GameScene>();
		}
		state_->Initialize();
		sceneChange_->FadeInStart();
	}
}