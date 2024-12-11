#pragma once
#include"Skill.h"
#include"Deck.h"


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

	Skills skills_;
	unique_ptr<Deck> deck_ = nullptr;
};