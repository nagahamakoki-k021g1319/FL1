/**
 * @file GameScene.h
 * @brief ゲームプレイシーン
 */
#pragma once
#include"Model.h"
#include"SceneState.h"
#include"Sprite.h"
#include"Audio.h"
#include"GameCamera.h"
#include "TGameCamera.h"
#include"CollisionManager.h"

#include"Player.h"
#include"Ground.h"
#include"FieldManager.h"
#include"CountCoin.h"

#include"GameManager.h"

#include"BaseMovie.h"

using namespace std;

class GameScene : public SceneState {
public:
	GameScene();
	~GameScene();
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
public:
	//ステージ番号
	static int stageNum_;
private:
	//カメラ
	unique_ptr<TGameCamera> gameCamera_ = nullptr;
	//プレイヤー
	unique_ptr<Player::Main> player_ = nullptr;
	//地面
	unique_ptr<Ground> ground_=nullptr;

	//地面モデル
	unique_ptr<Model> modelGround_ = nullptr;
	
	//フィールドマネージャー
	unique_ptr<FieldManager>fieldManager_ = nullptr;

	//コインカウント
	unique_ptr<CountCoin>countCoin_ = nullptr;
	//レールカメラ
	Transform railCameraPos_;

	unique_ptr<GameManager> gameManager_ = nullptr;

	unique_ptr<BaseMovie> movie_ = nullptr;
};