#pragma once
#include<map>
#include<string>
#include"Sprite.h"
#include"Button.h"

struct ScoreData{
	int cost;//消費体力
	int score;//素点
	int shield;//盾
	int concentration;//集中
	int condition;//好調
};

class Skill {
public:
	void SetScoreData(ScoreData scoreData) { scoreData_ = scoreData; };
	ScoreData GetScoreData() { return scoreData_; };

	bool CanUseSkill(ScoreData* scoreData, int hp);
	void Use(ScoreData* scoreData, int* hp, int maxScore = 0, float rate = 1);
	
public:
	std::string name_;
	ScoreData scoreData_;
	bool isOneTime_;//一度きり
	Button button_;
	Sprite explanation_;
	bool isSelected_;
};

class Skills {
public:

public:
	void Initilize();
	void AddSkill(std::string name, int score, int cost, int shield,int concentration,int condition, bool isOneTime);

	Skill GetSkill(std::string name);
private:
	std::map<std::string, Skill> skills_;

};