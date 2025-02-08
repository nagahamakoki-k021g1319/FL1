#include "BufUI.h"

BufUI::BufUI()
{
}

BufUI::~BufUI()
{
}

void BufUI::Initialize()
{
	qSprite_ = std::make_unique<Sprite>();
	qSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("q.png"));
	qSprite_->SetPozition({ 440,560 });
	qSprite_->Update();

	wSprite_ = std::make_unique<Sprite>();
	wSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("w.png"));
	wSprite_->SetPozition({ 540,560 });
	wSprite_->Update();

	eSprite_ = std::make_unique<Sprite>();
	eSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("e.png"));
	eSprite_->SetPozition({ 640,560 });
	eSprite_->Update();


}

void BufUI::Update()
{
	qSprite_->Update();
	wSprite_->Update();
	eSprite_->Update();
}

void BufUI::Draw()
{
	qSprite_->Draw();
	wSprite_->Draw();
	eSprite_->Draw();
}
