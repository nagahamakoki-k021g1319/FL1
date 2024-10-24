#include"Skill.h"
#include <random>
#include <algorithm>

void Skills::Initilize() {
	AddSkill("appeal", 9, 4, 0, false);
	AddSkill("pose", 2, 3, 2, false);
	AddSkill("twice", 8, 7, 0, true);
	AddSkill("expression", 0, 0, 4, true);
	AddSkill("face", 0, 1, 1, false);
}

void Skills::AddSkill(std::string name, int score, int cost, int shield, bool isOneTime) {
	Skill newSkill{};
	newSkill.name_ = name;
	newSkill.score_ = score;
	newSkill.cost_ = cost;
	newSkill.shield_ = shield;
	newSkill.isOneTime_ = isOneTime;

	skills_[name] = newSkill;
}

Skills::Skill Skills::GetSkill(std::string name) {
	return skills_.at(name);
}