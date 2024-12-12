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
	bool AddRandSkill();
	void AddRandSkillDraw(Skills skills);

	void Update(ScoreData* scoreData, int* hp);
	
	void SetDeck();
	void DrawSkill();
	void UseSkill(ScoreData* scoreData,int* hp);
	ScoreData GetChangedScoreData(ScoreData* scoreData);
	int GetChangedHp(ScoreData* scoreData);
	void Discard();
	void Shuffle();
	void ResetDeck();

	void SpriteSort();

	void DrawHand();
	void DrawList();
	void DrawDeck();
	void DrawAddSkill();

	bool IsUsedSkill();
	Skill GetUsedSkil();
	bool IsSelectedSkill();
	Skill GetSelectedSkill();
private:
	vector<Skill> hasSkills_;
	vector<Skill> deck_;
	vector<Skill> hand_;
	vector<Skill> discard_;
	vector<Skill> banish_ ;
	vector<Skill> addRandList_;

	Sprite deckSprite_;
	Sprite handSprite_;
	Sprite discardSprite_;
	Sprite banishSprite_;

	Vector2 handPos_[3];
	float addSelecthandPos_;
	Vector2 defaultHandPos_[3];

	bool canUseSkill_[3];
	int selectedSkillNum_;
	bool isUsedSkill_;
	Skill usedSkill_;
	bool isSelectedSkill_;
	Skill selectedSkill_;
};