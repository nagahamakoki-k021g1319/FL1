#include"Skill.h"
#include <random>
#include <algorithm>

void Skills::Initilize() {
	AddSkill("appeal", 14, 3, 0, 0, 0, false);
	AddSkill("pose", 6, 3, 4, 0, 0, false);
	AddSkill("twice", 10, 5, 0, 0, 0, true);
	AddSkill("expression", 0, 0, 7, 0, 0, true);
	AddSkill("face", 0, 1, 1, 3, 0, false);
	AddSkill("behavior", 0, 1, 1, 0, 3, false);

	AddSkill("step", 9, 4, 0, 0, 3, false);
	AddSkill("warmUp", 9, 4, 0, 4, 0, false);
	AddSkill("fanService", 16, 2, 0, 0, 0, false);
	AddSkill("talkTime", 38, 6, 0, 0, 0, true);
	AddSkill("stubborn", 0, 2, 5, 5, 0, true);
	AddSkill("sign", 0, 3, 0, 0, 7, true);
	AddSkill("breath", 0, 7, 0, 5, 4, true);
	AddSkill("will", 0, 4, 0, 4, 3, true);
	AddSkill("highFive", 23, 4, 0, 0, 0, true);
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
	newSkill.isSelected_ = false;

	skills_[name] = newSkill;
}

Skill Skills::GetSkill(std::string name) {
	return skills_.at(name);
}

bool Skill::CanUseSkill(ScoreData* scoreData, int hp) {
	int newHp;

	if (scoreData->shield >= scoreData_.cost) {
		return true;
	}
	else {
		newHp = (hp + scoreData->shield) - scoreData_.cost;
	}

	if (newHp >= 0) {
		return true;
	}
	return false;
}


void Skill::Use(ScoreData* scoreData, int* hp, int maxScore, float rate) {
	//体力計算
	if (scoreData->shield >= scoreData_.cost) {
		scoreData->shield -= scoreData_.cost;
	}
	else {
		scoreData_.cost -= scoreData->shield;
		scoreData->shield = 0;
		*(hp) -= scoreData_.cost;
	}

	//スコア計算
	if (scoreData_.score > 0) {
		int newScore = 0;
		//--基本--
		if (scoreData->condition > 0) {
			float addScore = 0;
			if (name_ == "highFive") {
				addScore = static_cast<float>(scoreData_.score + (scoreData->concentration * 2)) * 1.5f;
			}else {
				addScore = static_cast<float>(scoreData_.score + scoreData->concentration) * 1.5f;
			}
			newScore = scoreData->score + static_cast<int>(ceil(addScore * rate));
			if (maxScore > 0) {
				if (maxScore > newScore) {
					scoreData->score = newScore;
				}else {
					scoreData->score = maxScore;
				}
			}else {
				scoreData->score = newScore;
			}
		}
		else {
			if (name_ == "highFive") {
				newScore = scoreData->score + static_cast<int>(ceil((scoreData_.score + (scoreData->concentration * 2)) * rate));
			}else {
				newScore = scoreData->score + static_cast<int>(ceil((scoreData_.score + scoreData->concentration) * rate));
			}
			if (maxScore > 0) {
				if (maxScore > newScore) {
					scoreData->score = newScore;
				}
				else {
					scoreData->score = maxScore;
				}
			}
			else {
				scoreData->score = newScore;
			}
		}
		//------

		if (name_ == "twice") {
			if (scoreData->condition > 0) {
				float addScore = static_cast<float>(scoreData_.score + scoreData->concentration) * 1.5f;
				newScore = scoreData->score + static_cast<int>(ceil(addScore * rate));
				if (maxScore > 0) {
					if (maxScore > newScore) {
						scoreData->score = newScore;
					}
					else {
						scoreData->score = maxScore;
					}
				}
				else {
					scoreData->score = newScore;
				}
			}
			else {
				newScore = scoreData->score + static_cast<int>(ceil((scoreData_.score + scoreData->concentration) * rate));
				if (maxScore > 0) {
					if (maxScore > newScore) {
						scoreData->score = newScore;
					}
					else {
						scoreData->score = maxScore;
					}
				}
				else {
					scoreData->score = newScore;
				}
			}
		}
	}

	//バフ追加
	scoreData->concentration += scoreData_.concentration;
	if (scoreData->condition == 0) {
		scoreData->condition += scoreData_.condition;
	}
	else if (scoreData->condition > 0) {
		scoreData->condition += scoreData_.condition;
		scoreData->condition--;
	}
	scoreData->shield += scoreData_.shield;
}