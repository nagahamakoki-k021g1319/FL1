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

	bool IsUsedSkill();
	Skill GetUsedSkil();
private:
	vector<Skill> hasSkills_;
	vector<Skill> deck_;
	vector<Skill> hand_;
	vector<Skill> discard_;
	vector<Skill> banish_ ;

	Sprite deckSprite_;
	Sprite handSprite_;
	Sprite discardSprite_;
	Sprite banishSprite_;

	Vector2 handPos_[3];
	float addSelecthandPos_;
	Vector2 defaultHandPos_[3];

	int selectedSkill_;
	bool isUsedSkill_;
	Skill usedSkill_;
};