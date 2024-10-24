#pragma once
#include<memory>
#include<vector>

#include"Skill.h"
#include"Sprite.h"
#include"SpriteLoader.h"


using namespace std;

class Deck {
public:
	void Initilize(Skills skills);
	void AddSkill(Skills skills, std::string name);

	void Update();
	
	void SetDeck();
	void DrawSkill();
	void UseSkill();
	void Discard();
	void Shuffle();

	void SpriteSort();

	void DrawHand();
	void DrawList();
	void DrawDeck();

private:
	vector<Skills::Skill> hasSkills_;
	vector<Skills::Skill> deck_;
	vector<Skills::Skill> hand_;
	vector<Skills::Skill> discard_;
	vector<Skills::Skill> banish_ ;

	Sprite deckSprite_;
	Sprite handSprite_;
	Sprite discardSprite_;
	Sprite banishSprite_;

	Skills::Skill usedSkill_;
};