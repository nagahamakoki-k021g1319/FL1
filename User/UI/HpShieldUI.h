#pragma once
#include "Sprite.h"
#include "BarGraph.h"
#include "Number.h"
#include <memory>

using namespace std;

class HpShieldUI
{
public:
	HpShieldUI();
	~HpShieldUI();

	void Initialize();
	void Update();
	void Draw();

	void GetHPpt(int* num);
	void GetShieldpt(int* num);

private:
	int* hp_;
	int* shield_;

	Vector2 hpSize_;
	Vector2 shieldSize_;

	Vector2 hpPos_;
	Vector2 shieldPos_;

	std::unique_ptr<Sprite>	hpSprite_;
	std::unique_ptr<Sprite>	shieldSprite_;

	std::unique_ptr<BarGraph> hpBar_;
	std::unique_ptr<BarGraph> shieldBar_;

	std::unique_ptr<Number>	hpNumber_;
	std::unique_ptr<Number>	shieldNumber_;
};

