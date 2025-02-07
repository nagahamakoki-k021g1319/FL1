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
	shieldSize_ = { 15,30 };

	hpNumber_ = std::make_unique<Number>();
	hpNumber_->Initialize();
	shieldNumber_ = std::make_unique<Number>();
	shieldNumber_->Initialize();

	hpBar_ = make_unique<BarGraph>();
	hpBar_->SetParams(float(*hp_));
	hpBar_->SetSize(hpSize_);
	hpBar_->Initialize({ 50,195 }, "orange.png");
	oldHp_ = *hp_;

	shieldBar_ = make_unique<BarGraph>();
	shieldBar_->SetParams(float(*shield_));
	shieldBar_->SetSize(shieldSize_);
	shieldBar_->Initialize({ 50,190 }, "cian.png");
	oldShield_ = *shield_;

	hpSprite_ = std::make_unique<Sprite>();
	hpSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("hp.png"));
	hpSprite_->SetPozition({ 0,130 });
	hpSprite_->SetColor({ 1,1,0,1 });
	hpSprite_->Update();

	shieldSprite_ = std::make_unique<Sprite>();
	shieldSprite_->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("shield.png"));
	shieldSprite_->SetPozition({ 130,130 });
	shieldSprite_->SetColor({ 0,1,1,1 });
	shieldSprite_->Update();

	time_ = 0;
}

void HpShieldUI::Update()
{
	hpBar_->AutoEaseParms((float)oldHp_,(float)*hp_);

	shieldBar_->AutoEaseParms((float)oldShield_, (float)*shield_);

	//if (oldShield_ != *shield_) {
	//	timeStart = true;
	//}
	//if (timeStart) {
	//	if (time_<=easeMaxTime) {
	//		time_++;
	//	}
	//	else {
	//		time_ = easeMaxTime;
	//		timeStart = false;
	//		oldShield_ = *shield_;
	//	}
	//	easetime = (float)time_ / (float)easeMaxTime;
	//	shieldBar_->EaseParms((float)oldShield_, (float)*shield_, easetime);
	//}
	//else {
	//	time_ = 0;
	//	easetime = 0;
	//}

	hpBar_->Update();
	shieldBar_->Update();
}

void HpShieldUI::Draw()
{
	shieldBar_->Draw();
	hpBar_->Draw();

	hpSprite_->Draw();
	shieldSprite_->Draw();

	shieldNumber_->Draw({ 245,195 }, *shield_, 0.4f);
	hpNumber_->Draw({ 60,234 }, *hp_, 0.4f);
}

void HpShieldUI::GetHPpt(int* num)
{
	hp_ = num;
}

void HpShieldUI::GetShieldpt(int* num)
{
	shield_ = num;
}

void HpShieldUI::GetScoreData(ScoreData* data)
{
	scoreData_ = *data;
}
