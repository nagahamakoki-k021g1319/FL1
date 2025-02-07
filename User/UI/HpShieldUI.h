#pragma once
#include "Sprite.h"
#include"Skill.h"
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

	int oldHp_;
	int oldShield_;

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

	std::unique_ptr<Number>	changeHpNumber_;
	std::unique_ptr<Number>	changeShieldNumber_;

	std::unique_ptr<Sprite>	hpMinusSprite_;
	std::unique_ptr<Sprite>	shieldPlusSprite_;
	std::unique_ptr<Sprite>	shieldMinusSprite_;

private:
	uint32_t time_;
	uint32_t easeMaxTime = 40;
	float easetime;
	bool timeEnd = false;
	bool timeStart;
};

