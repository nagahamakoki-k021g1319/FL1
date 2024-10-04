/**
 * @file GameScene.cpp
 * @brief ゲームプレイシーン
 */

#include "GameScene.h"
#include "BaseFieldObjectManager.h"
#include "Collision.h"
#include "Easing.h"
#include "FbxLoader.h"
#include "GoalObject.h"
#include "LightGroup.h"
#include "Model.h"
#include "ObjLoader.h"
#include "Object3D.h"
#include "SceneManager.h"
#include "SpriteLoader.h"
#include "StartMovie.h"

int GameScene::stageNum_ = 1;

GameScene::GameScene() {}

// 初期化
void GameScene::Initialize() {
	// カメラ生成
	gameCamera_ = make_unique<TGameCamera>();
	gameCamera_->Initialize(WinApp::window_width, WinApp::window_height);

	// カメラセット
	FBXObject3d::SetCamera(gameCamera_.get());
	Object3d::SetCamera(gameCamera_.get());
	ParticleManager::SetCamera(gameCamera_.get());

	railCameraPos_.Initialize();
	railCameraPos_.position.z = -150.0f;

	// プレイヤー
	player_ = make_unique<Player::Main>();
	player_->Initialize();

	// 地面
	ObjLoader* objLoader = ObjLoader::GetInstance();
	ground_ = make_unique<Ground>(
	    objLoader->GetModel("Ground"), Vector3(0.0f, 0.0f, -150.0f), Vector3(10.0f, 10.0f, 40.0f),
	    gameCamera_.get());

	// フィールドマネージャー
	fieldManager_ = make_unique<FieldManager>();
	fieldManager_->Initialize();
	fieldManager_->Load(to_string(stageNum_));

	// 当たり判定マネージャー初期化
	CollisionManager::GetInstance()->Initialize();

	// コインカウント
	countCoin_ = make_unique<CountCoin>();
	countCoin_->Initialize();

	gameManager_ = std::make_unique<GameManager>();
	gameManager_->Init();

	movie_ = std::make_unique<StartMovie>();
	movie_->Init();
	movie_->Update(gameCamera_.get());
}

GameScene::~GameScene() {
	LightGroup::GetInstance()->ClearCircleShadow();
	CollisionManager::GetInstance()->Finalize();
	BaseFieldObjectManager::Clear();
}

// 更新
void GameScene::Update() {
	railCameraPos_.position += {0, 0, 0.5f};
	railCameraPos_.UpdateMat();

	if (!movie_->GetIsFinish()) {
		movie_->Update(gameCamera_.get());
	} else {
		gameCamera_->DebugCameraUpdate();
	}

	gameCamera_->SetParentTF(railCameraPos_);
	gameCamera_->Update();

	TGameCamera::gameCamera_ = gameCamera_.get();

	player_->Update(railCameraPos_);

	ground_->Update();
	CollisionManager::GetInstance()->CheakAllCol();

	StateTransition();
}

void GameScene::ObjectDraw() {

	ground_->Draw();
	BaseFieldObjectManager::ManagerBaseFieldObject();
#ifdef _DEBUG
	CollisionManager::GetInstance()->DrawCollider();
#endif
}

void GameScene::FbxDraw() { player_->FbxDraw(); }

void GameScene::SpriteDraw() {
	countCoin_->Draw();
	player_->ParticleDraw();
	countCoin_->Draw();

	movie_->Draw();
}

void GameScene::StateTransition() {
	if (Input::GetInstance()->TriggerKey(DIK_T) || GoalObject::GetGoaled()) {
		sceneManager_->TransitionTo(SceneManager::SCENE::TITLE);
	}
}