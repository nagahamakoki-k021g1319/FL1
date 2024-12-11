/**
 * @file TitelScene.cpp
 * @brief タイトルシーン
 */
#include"TitleScene.h"
#include"SceneManager.h"

#include"FbxLoader.h"
#include"SpriteLoader.h"
#include"LightGroup.h"

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

	//donut_ = make_unique<DonutGraph>();
	//donut_->SetSizeGraph(Vector2(100, 100));
	//donut_->Initialize(MyEngine::SpriteCommon::GetInstance()->GetDxCommon());
	
	// 
	//
	uint32_t division = 12;
	Vector2 startpos = {250,30};
	barGraph_ = make_unique<BarGraph>();
	barGraph_->SetDivision(division);
	barGraph_->NowProgres(division);
	barGraph_->SetStartPos(startpos);
	barGraph_->Initialize();


}

TitleScene::~TitleScene() {
	LightGroup::GetInstance()->ClearCircleShadow();
}

// 更新
void TitleScene::Update() {
	gameCamera_->Update();
	barGraph_->Update();

	StateTransition();
}

void TitleScene::ObjectDraw() {

	//donut_->Draw(MyEngine::SpriteCommon::GetInstance()->GetDxCommon()->GetCommandList());
}

void TitleScene::FbxDraw() {
}

void TitleScene::SpriteDraw() {
	barGraph_->Draw();
}

void TitleScene::StateTransition() {
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneManager_->TransitionTo(SceneManager::SCENE::SELECT);
	}
}