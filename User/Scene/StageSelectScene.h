/**
 * @file StageSelectScene.h
 * @brief タイトルシーン
 */
#pragma once
#include"SceneState.h"
#include"Model.h"
#include"Sprite.h"
#include"Audio.h"
#include"GameCamera.h"
#include"FBXObject3d.h"
#include"Object3d.h"
#include"ParticleManager.h"

using namespace std;

class StageSelectScene : public SceneState {
public:
	StageSelectScene();
	~StageSelectScene();
	/**
	 * @brief 初期化
	*/
	void Initialize();
	/**
	 * @brief 更新
	*/
	void Update() override;
	/**
	 * @brief obj描画
	*/
	void ObjectDraw() override;
	/**
	 * @brief fbx描画
	*/
	void FbxDraw() override;
	/**
	 * @brief スプライト描画
	*/
	void SpriteDraw() override;

private:
	/**
	 * @brief シーン移行
	*/
	void StateTransition() override;

private:
	//カメラ
	unique_ptr<GameCamera> gameCamera_ = nullptr;

	//スプライト
	unique_ptr<Sprite> stageSelectPic_ = nullptr;
};