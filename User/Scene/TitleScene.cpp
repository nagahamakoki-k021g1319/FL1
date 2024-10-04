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

	//スプライト
	SpriteLoader* spriteLoader = SpriteLoader::GetInstance();
	/*タイトル*/
	titlePic_ = make_unique<Sprite>();
	titlePic_->Initialize(SpriteCommon::GetInstance(), spriteLoader->GetTextureIndex("title.png"));
	Vector2 titlePos = titlePic_->GetTexSize();
	titlePos = titlePos * 2.0f;
	titlePic_->SetSize(titlePos);
	/*スペース*/
	spacePic_ = make_unique<Sprite>();
	spacePic_->Initialize(SpriteCommon::GetInstance(), spriteLoader->GetTextureIndex("pushkey.png"));
	spacePic_->SetAnchorPoint({ 0.5f,0.5f });
	spacePic_->SetPozition({ WinApp::window_width/2.0f,600.0f});
}

TitleScene::~TitleScene() {
	LightGroup::GetInstance()->ClearCircleShadow();
}

// 更新
void TitleScene::Update() {
	gameCamera_->Update();
	titlePic_->Update();
	spacePic_->Update();

	StateTransition();
	flashTime++;
	if (flashTime>=flashTimer)
	{
		isFlash ^= 1;
		flashTime = 0;
	}
}

void TitleScene::ObjectDraw() {

}

void TitleScene::FbxDraw() {
}

void TitleScene::SpriteDraw() {
	titlePic_->Draw();
	if (isFlash)
	{
		spacePic_->Draw();
	}
}

void TitleScene::StateTransition() {
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		sceneManager_->TransitionTo(SceneManager::SCENE::SELECT);
	}
}