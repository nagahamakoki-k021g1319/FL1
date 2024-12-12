/**
 * @file TitelScene.cpp
 * @brief タイトルシーン
 */
#include"TitleScene.h"
#include"SceneManager.h"

#include"FbxLoader.h"
#include"SpriteLoader.h"
#include"LightGroup.h"
#include <imgui.h>

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
	blockBarGraph_ = make_unique<BlockGraph>();
	blockBarGraph_->SetDivision(division);
	blockBarGraph_->NowProgres(division);
	blockBarGraph_->SetStartPos(startpos);
	blockBarGraph_->Initialize();

	barGraph_ = make_unique<BarGraph>();
	barGraph_->Initialize({250,70});
	HPkari = 100;
	barGraph_->SetHP(HPkari);

	title_ = std::make_unique<Sprite>();
	title_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("title.png"));
}

TitleScene::~TitleScene() {
	LightGroup::GetInstance()->ClearCircleShadow();
}

// 更新
void TitleScene::Update() {
	gameCamera_->Update();

	barGraph_->SetHP(HPkari);
	blockBarGraph_->Update();
	barGraph_->Update();
	int hp = (int)HPkari;
	ImGui::Begin("playerHP");
	ImGui::SliderInt("HP", &hp, 0, 100);
	ImGui::End();
	HPkari = (uint32_t)hp;

	title_->Update();

	StateTransition();
}

void TitleScene::ObjectDraw() {

	//donut_->Draw(MyEngine::SpriteCommon::GetInstance()->GetDxCommon()->GetCommandList());
}

void TitleScene::FbxDraw() {
}

void TitleScene::SpriteDraw() {
	title_->Draw();
	blockBarGraph_->Draw();
	barGraph_->Draw();
	
}

void TitleScene::StateTransition() {
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneManager_->TransitionTo(SceneManager::SCENE::SELECT);
	}
}