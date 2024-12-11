#pragma once
#include<map>
#include<string>
#include"Sprite.h"

struct ScoreData{
	int cost_;//消費体力
	int score_;//素点
	int shield_;//盾
	int concentration_;//集中
	int condition_;//好調
};

class Skill {
public:
	void SetScoreData(ScoreData scoreData) { scoreData_ = scoreData; };
	ScoreData GetScoreData() { return scoreData_; };
public:
	std::string name_;
	ScoreData scoreData_;
	bool isOneTime_;//一度きり
	Sprite sprite_;
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