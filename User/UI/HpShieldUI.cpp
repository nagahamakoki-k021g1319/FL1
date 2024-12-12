#include "HpShieldUI.h"


HpShieldUI::HpShieldUI()
{
}

HpShieldUI::~HpShieldUI()
{
}

void HpShieldUI::Initialize()
{
	hpSize_ = { 5,20 };
	shieldSize_ = { 15,30 };

	hpNumber_ = std::make_unique<Number>();
	hpNumber_->Initialize();
	shieldNumber_ = std::make_unique<Number>();
	shieldNumber_->Initialize();

	hpBar_ = make_unique<BarGraph>();
	hpBar_->SetParams(*hp_);
	hpBar_->SetSize(hpSize_);
	hpBar_->Initialize({ 50,195 },"orange.png");

	shieldBar_ = make_unique<BarGraph>();
	shieldBar_->SetParams(*shield_);
	shieldBar_->SetSize(shieldSize_);
	shieldBar_->Initialize({ 50,190 },"cian.png");

	hpSprite_ = std::make_unique<Sprite>();
	hpSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("hp.png"));
	hpSprite_->SetPozition({ 0,130 });
	hpSprite_->Update();

	shieldSprite_ = std::make_unique<Sprite>();
	shieldSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("shield.png"));
	shieldSprite_->SetPozition({ 130,130 });
	shieldSprite_->Update();
}

void HpShieldUI::Update()
{
	hpBar_->SetParams(*hp_);
	shieldBar_->SetParams(*shield_);
	hpBar_->Update();
	shieldBar_->Update();
}

void HpShieldUI::Draw()
{
	shieldBar_->Draw();
	hpBar_->Draw();

	hpSprite_->Draw();
	shieldSprite_->Draw();

	shieldNumber_->Draw({ 190,194 }, *shield_, 0.4f);
	hpNumber_->Draw({ 60,194 }, *hp_, 0.4f);
}

void HpShieldUI::GetHPpt(int* num)
{
	hp_ = num;
}

void HpShieldUI::GetShieldpt(int* num)
{
	shield_ = num;
}
