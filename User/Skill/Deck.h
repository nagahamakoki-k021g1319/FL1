#pragma once
#include<memory>
#include<vector>

#include"Skill.h"

using namespace std;

class Deck {
public:
	void Initilize(Skills skills);
	void AddSkill();

	void Update();
	
	void SetDeck();
	void DrawSkill();
	Skills::Skill UseSkill();
	void Discard();
	void Shuffle();

	void DrawHand();

private:
	vector<Skills::Skill> hasSkills_;
	vector<Skills::Skill> deck_;
	vector<Skills::Skill> hand_;
	vector<Skills::Skill> discard_;
	vector<Skills::Skill> banish_ ;
};