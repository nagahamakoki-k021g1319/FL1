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
	int score_;

	int hp_;
	int shield_;
	int concentration_;
	int condition_;

	std::unique_ptr<Sprite>	scoreSprite_;
	std::unique_ptr<Sprite>	hpSprite_;
	std::unique_ptr<Sprite>	shieldSprite_;
	std::unique_ptr<Sprite>	concentrationSprite_;
	std::unique_ptr<Sprite>	conditionSprite_;

	std::unique_ptr<Number>	scoreNumber_;
	std::unique_ptr<Number>	hpNumber_;
	std::unique_ptr<Number>	shieldNumber_;
	std::unique_ptr<Number>	concentrationNumber_;
	std::unique_ptr<Number>	conditionNumber_;

	Skills skills_;
	unique_ptr<Deck> deck_ = nullptr;
};