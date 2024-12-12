#pragma once
#include"Skill.h"
#include"Deck.h"
#include"Number.h"


class Player {
public:
	void Initilize();
	void Update();
	void Draw();
private:
	//スコア関連
	int score_;
	int hp_;
	int shield_;
	int concentration_;
	int condition_;

	//スコア予想
	int changeScore_;
	int changeHp_;
	int changeShield_;
	int changeConcentration_;
	int changeCondition_;

	std::unique_ptr<Sprite>	scoreSprite_;
	std::unique_ptr<Sprite>	scorePlusSprite_;
	std::unique_ptr<Sprite>	hpSprite_;
	std::unique_ptr<Sprite>	hpMinusSprite_;
	std::unique_ptr<Sprite>	shieldSprite_;
	std::unique_ptr<Sprite>	shieldPlusSprite_;
	std::unique_ptr<Sprite>	shieldMinusSprite_;
	std::unique_ptr<Sprite>	concentrationSprite_;
	std::unique_ptr<Sprite>	concentrationPlusSprite_;
	std::unique_ptr<Sprite>	conditionSprite_;
	std::unique_ptr<Sprite>	conditionPlusSprite_;

	std::unique_ptr<Number>	scoreNumber_;
	std::unique_ptr<Number>	hpNumber_;
	std::unique_ptr<Number>	shieldNumber_;
	std::unique_ptr<Number>	concentrationNumber_;
	std::unique_ptr<Number>	conditionNumber_;

	std::unique_ptr<Number>	changeScoreNumber_;
	std::unique_ptr<Number>	changeHpNumber_;
	std::unique_ptr<Number>	changeShieldNumber_;
	std::unique_ptr<Number>	changeConcentrationNumber_;
	std::unique_ptr<Number>	changeConditionNumber_;

	Skills skills_;
	unique_ptr<Deck> deck_ = nullptr;
};