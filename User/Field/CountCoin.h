#pragma once
#include"Sprite.h"
#include<memory>
class CountCoin
{
public:
	void Initialize();

	void Draw();
	static int32_t num_;
private:
	const int32_t digit_ = 2;
	std::unique_ptr<Sprite> count_[2];
	char strNum_[3];
};

