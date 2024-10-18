#include"Skill.h"
#include <random>
#include <algorithm>

void Skills::Initilize() {
	AddSkill("appeal", 9, 4, 0);
	AddSkill("pose", 2, 3, 2);
	AddSkill("twice", 8, 7, 0);
	AddSkill("expression", 0, 0, 4);
	AddSkill("face", 0, 1, 1);
}

void Skills::AddSkill(std::string name, int score, int cost, int shield) {
	Skill newSkill{};
	newSkill.name_ = name;
	newSkill.score_ = score;
	newSkill.cost_ = cost;
	newSkill.shield_ = shield;
	newSkill.sprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex(name+".png"));

	skills_[name] = newSkill;
}

Skills::Skill Skills::GetSkill(std::string name) {
	return skills_.at(name);
}