#pragma once
#include"Skill.h"
#include"Deck.h"
#include"Number.h"


class Player {
public:
	void Initilize();
	void Update();
	void Draw();

	void DrawStatus();
	bool IsTurnEnd();
	int GetScore() { return scoreData_.score; };
	void DeckReset();
	void ScoreReset();
	void AddStatus(int add,int type);
	void AddRandSkillDraw() { deck_->AddRandSkillDraw(skills_); };
	bool addRandSkill() { return deck_->AddRandSkill(); };
	void DrawAddSkill() { addSelectSprite_->Draw(); deck_->DrawAddSkill(); };

	int* GetHP() { return &hp_; }
	int* GetShield() { return &scoreData_.shield; }
	ScoreData GetScoreData() { return scoreData_; }
  
private:
	//スコア関連
	ScoreData scoreData_;
	int maxHp_;
	int hp_;

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
	std::unique_ptr<Sprite>	addSelectSprite_;

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

	std::unique_ptr<Number>	statusNumber_[3];

	Skills skills_;
	unique_ptr<Deck> deck_ = nullptr;
	
	bool isTurnEnd_;
	int status_[3];
};