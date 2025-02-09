#include "HpShieldUI.h"
#include "Input.h"

HpShieldUI::HpShieldUI()
{
}

HpShieldUI::~HpShieldUI()
{
}

void HpShieldUI::Initialize()
{
	hpSize_ = { 5,20 };
	shieldSize_ = { 7,30 };

	hpNumber_ = std::make_unique<Number>();
	hpNumber_->Initialize();
	shieldNumber_ = std::make_unique<Number>();
	shieldNumber_->Initialize();

	hpBar_ = make_unique<BarGraph>();
	hpBar_->SetParams(float(*hp_));
	hpBar_->SetSize(hpSize_);
	hpBar_->Initialize({ 50,65 }, "orange.png");
	oldHp_ = *hp_;

	shieldBar_ = make_unique<BarGraph>();
	shieldBar_->SetParams(float(*shield_));
	shieldBar_->SetSize(shieldSize_);
	shieldBar_->Initialize({ 45,60 }, "cian.png");
	oldShield_ = *shield_;

	shieldSprite_ = std::make_unique<Sprite>();
	shieldSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("shield.png"));
	shieldSprite_->SetPozition({ 256,63 });
	shieldSprite_->SetColor({ 0,1,1,1 });
	shieldSprite_->Update();

	hpSprite_ = std::make_unique<Sprite>();
	hpSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("HpGreen.png"));
	hpSprite_->SetPozition({ 135,90 });
	hpSprite_->Update();

	hpFrameSprite_ = std::make_unique<Sprite>();
	hpFrameSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("hpBarFrame.png"));
	hpFrameSprite_->SetPozition({ 45,60 });
	hpFrameSprite_->Update();

	time_ = 0;
}

void HpShieldUI::Update()
{
	hpFrameSprite_->Update();
	hpBar_->AutoEaseParms((float&)oldHp_,(float)*hp_);
	shieldBar_->AutoEaseParms((float&)oldShield_, (float)*shield_);

	hpBar_->Update();
	shieldBar_->Update();
	shieldSprite_->Update();
	hpSprite_->Update();
}

void HpShieldUI::Draw()
{
	hpFrameSprite_->Draw();

	shieldBar_->Draw();
	hpBar_->Draw();

	hpSprite_->Draw();
	shieldSprite_->Draw();

	if (*shield_ >= 10) {
		shieldNumber_->Draw({ 244,65 }, *shield_, 0.4f);
	}else {
		shieldNumber_->Draw({ 250,65 }, *shield_, 0.4f);
	}
	hpNumber_->Draw({ 155,90 }, *hp_, 0.4f);
}

void HpShieldUI::GetHPpt(int* num)
{
	hp_ = num;
}

void HpShieldUI::GetShieldpt(int* num)
{
	shield_ = num;
}