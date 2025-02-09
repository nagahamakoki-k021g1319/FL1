#pragma once
#include<memory>
#include<vector>

#include"Skill.h"
#include"Sprite.h"
#include"SpriteLoader.h"
#include"Audio.h"
#include"Number.h"

using namespace std;

class Deck {
public:
	void Initilize(Skills skills);
	void AddSkill(Skills skills, std::string name);
	bool AddRandSkill();
	void AddRandSkillDraw(Skills skills);

	void Update(ScoreData* scoreData, int* hp, int maxScore = 0, float rate = 1.0f);
	
	void SetDeck();
	void DrawSkill();
	void FirstDrawSkill();
	void UseSkill(ScoreData* scoreData, int* hp, int maxScore = 0, float rate = 1.0f);
	ScoreData GetChangedScoreData(ScoreData* scoreData, int maxScore = 0, float rate = 1);
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
	bool IsReloard();
private:
	vector<Skill> hasSkills_;
	vector<Skill> deck_;
	vector<Skill> hand_;
	vector<Skill> discard_;
	vector<Skill> banish_;
	vector<Skill> addRandList_;

	Sprite deckSprite_;
	Sprite discardSprite_;
	Sprite banishSprite_;
	Sprite deckBackSprite_;

	Vector2 handPos_[3];
	float addSelecthandPos_;
	Vector2 defaultHandPos_[3];

	bool canUseSkill_[3];
	int selectedSkillNum_;
	bool isUsedSkill_;
	Skill usedSkill_;
	bool isSelectedSkill_;
	Skill selectedSkill_;

	Button skipButton_;

  Audio* audio_ = nullptr;
	IXAudio2SourceVoice* pSourceVoice_;
	Audio* audio2_ = nullptr;
	IXAudio2SourceVoice* pSourceVoice2_;

	Button reloadButton_;
	int reloadNum_;
	Number reloadNumber_;
};