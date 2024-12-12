#include"Skill.h"
#include <random>
#include <algorithm>

void Skills::Initilize() {
	AddSkill("appeal", 9, 4, 0, 0, 0, false);
	AddSkill("pose", 2, 3, 2, 0, 0, false);
	AddSkill("twice", 8, 7, 0, 0, 0,true);
	AddSkill("expression", 0, 0, 4, 0, 0, true);
	AddSkill("face", 0, 1, 1, 2, 0, false);
	AddSkill("behavior", 0, 1, 1, 0, 2, false);
}

void Skills::AddSkill(std::string name, int score, int cost, int shield, int concentration, int condition, bool isOneTime) {
	Skill newSkill{};
	newSkill.name_ = name;
	ScoreData newScoreData;
	newScoreData.score = score;
	newScoreData.cost = cost;
	newScoreData.shield = shield;
	newScoreData.concentration = concentration;
	newScoreData.condition = condition;
	newSkill.SetScoreData(newScoreData);
	newSkill.isOneTime_ = isOneTime;

	skills_[name] = newSkill;
}

Skill Skills::GetSkill(std::string name) {
	return skills_.at(name);
}

bool Skill::CanUseSkill(ScoreData scoreData, int hp) {	
	int newHp;

	if (scoreData.shield >= scoreData_.cost) {
		return true;
	}else {
		newHp = (hp + scoreData.shield) - scoreData_.cost;
	}

	if (newHp >= 0) {
		return true;
	}
	return false;
}