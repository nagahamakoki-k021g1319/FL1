#include "CountCoin.h"
#include"SpriteLoader.h"
#include<stdio.h>
#include"Input.h"
using namespace MyEngine;

int32_t CountCoin::num_ = 0;

void CountCoin::Initialize()
{
	for (size_t i = 0; i < digit_; i++)
	{
		count_[i] = std::make_unique<Sprite>();
		count_[i]->Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("nums.png"));
		count_[i]->SetPozition({ 20.0f+(40.0f*i), 50.0f});
		count_[i]->SetTexSize({ 64.0f,64.0f });
		count_[i]->SetSize({ 64.0f,64.0f });
		count_[i]->Update();
	}
	num_ = 0;
}

void CountCoin::Draw()
{
	if (num_>99)
	{
		num_ = 0;
	}
	sprintf_s(strNum_, sizeof(strNum_), "%02d", num_);
	for (size_t i = 0; i < digit_; i++)
	{
		strNum_[i] -= 48;
		count_[i]->SetTexLeftTop({ 64.0f*strNum_[i],0.0f});
		count_[i]->Update();
		count_[i]->Draw();
	}
}
