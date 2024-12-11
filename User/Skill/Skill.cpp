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
	newScoreData.score_ = score;
	newScoreData.cost_ = cost;
	newScoreData.shield_ = shield;
	newScoreData.concentration_ = concentration;
	newScoreData.condition_ = condition;
	newSkill.SetScoreData(newScoreData);
	newSkill.isOneTime_ = isOneTime;

	skills_[name] = newSkill;
}

Skill Skills::GetSkill(std::string name) {
	return skills_.at(name);
}