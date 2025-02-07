#include"Deck.h"
#include <random>
#include <algorithm>
#include"Input.h"
#include <set>

void Deck::Initilize(Skills skills) {
	AddSkill(skills, "appeal");
	AddSkill(skills, "appeal");
	AddSkill(skills, "pose");
	AddSkill(skills, "twice");
	AddSkill(skills, "expression");
	AddSkill(skills, "expression");
	AddSkill(skills, "face");
	AddSkill(skills, "face");
	AddSkill(skills, "behavior");

	SetDeck();
	Shuffle();

	deckSprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("deck.png"));
	deckSprite_.SetPozition({ 900,0 });
	discardSprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("discard.png"));
	discardSprite_.SetPozition({ 900,300 });
	banishSprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("banish.png"));
	banishSprite_.SetPozition({ 900,560 });

	handSprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("hand.png"));
	handSprite_.SetPozition({ 440,430 });

	addSelecthandPos_ = -20;
	defaultHandPos_[0] = { 440,500 };
	defaultHandPos_[1] = { 540,500 };
	defaultHandPos_[2] = { 640,500 };
	handPos_[0] = defaultHandPos_[0];
	handPos_[1] = defaultHandPos_[1];
	handPos_[2] = defaultHandPos_[2];
	isUsedSkill_ = false;
	isSelectedSkill_ = false;
	selectedSkillNum_ = -1;
}

void Deck::AddSkill(Skills skills, std::string name) {
	Skill newSkill = skills.GetSkill(name);
	newSkill.sprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex(newSkill.name_ + ".png"));
	newSkill.sprite_.SetSize({ 64,64 });
	hasSkills_.push_back(newSkill);
}

void Deck::AddRandSkillDraw(Skills skills) {
	string skillName[6];
	skillName[0] = "step";
	skillName[1] = "warmUp";
	skillName[2] = "fanService";
	skillName[3] = "talkTime";
	skillName[4] = "stubborn";
	skillName[5] = "sign";

	addRandList_.clear();

	std::set<int> uniqueNumbers;
	while (uniqueNumbers.size() < 3) {
		int number = rand() % 6;//スキルカードの種類数
		uniqueNumbers.insert(number);
	}


	for (int i = 0; i < 3; i++) {
		auto it = uniqueNumbers.begin();
		std::advance(it, i);
		Skill newSkill = skills.GetSkill(skillName[*it]);
		newSkill.sprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex(newSkill.name_ + ".png"));
		newSkill.sprite_.SetSize({ 64,64 });
		newSkill.sprite_.SetPozition({440.0f+100.0f*static_cast<float>(i),450});
		addRandList_.push_back(newSkill);
	}
}

bool Deck::AddRandSkill() {
	if (Input::GetInstance()->TriggerKey(DIK_Q)) {
		hasSkills_.push_back(addRandList_[0]);
		return true;
	}else if (Input::GetInstance()->TriggerKey(DIK_W)) {
		hasSkills_.push_back(addRandList_[1]);
		return true;
	}else if (Input::GetInstance()->TriggerKey(DIK_E)) {
		hasSkills_.push_back(addRandList_[2]);
		return true;
	}else if (Input::GetInstance()->TriggerKey(DIK_S)) {
		return true;
	}
	return false;
}

void Deck::SetDeck() {
	copy(hasSkills_.begin(), hasSkills_.end(), back_inserter(deck_));
}

void Deck::Update(ScoreData* scoreData, int* hp, int maxScore, float rate) {
	UseSkill(scoreData, hp, maxScore,rate);

	//スキップ
	if (Input::GetInstance()->TriggerKey(DIK_S)) {
		*(hp) += 2;
		const int maxHp = 40;
		if (*(hp) > maxHp) {
			*(hp) = maxHp;
		}
		if (scoreData->condition > 0) {
			scoreData->condition--;
		}
		isUsedSkill_ = true;
		Discard();
		DrawSkill();
	}

	SpriteSort();
}

Skill Deck::GetUsedSkil() {
	return usedSkill_;
};

Skill Deck::GetSelectedSkill() {
	return selectedSkill_;
};

bool Deck::IsUsedSkill() {
	if (isUsedSkill_ == true) {
		isUsedSkill_ = false;
		return true;
	}
	return false;
}

bool Deck::IsSelectedSkill() {
	if (isSelectedSkill_ == true) {
		return true;
	}
	return false;
}

void Deck::DrawSkill() {
	if (hand_.size() != 3) {
		int drawNum = 3;
		std::size_t deckNum = deck_.size();
		std::vector<int> indices;



		if (deckNum >= drawNum) {
			while (indices.size() < 3) {
				int randIndex = rand() % deck_.size();
				if (std::find(indices.begin(), indices.end(), randIndex) == indices.end()) {
					indices.push_back(randIndex);
				}
			}
			std::sort(indices.rbegin(), indices.rend());
			for (int index : indices) {
				hand_.push_back(deck_[index]); // hand_ に追加
				deck_.erase(deck_.begin() + index); // deck_ から削除
			}
		}else {
			int num = 0;
			while (indices.size() < deckNum) {
				int randIndex = rand() % deck_.size();
				if (std::find(indices.begin(), indices.end(), randIndex) == indices.end()) {
					indices.push_back(randIndex);
					num++;
				}
			}

			std::sort(indices.rbegin(), indices.rend());
			for (int index : indices) {
				hand_.push_back(deck_[index]); // hand_ に追加
				deck_.erase(deck_.begin() + index); // deck_ から削除
			}
			indices.clear();
			copy(discard_.begin(), discard_.end(), back_inserter(deck_));
			discard_.clear();
			Shuffle();

			while (indices.size() < drawNum - num) {
				int randIndex = rand() % deck_.size();
				if (std::find(indices.begin(), indices.end(), randIndex) == indices.end()) {
					indices.push_back(randIndex);
				}
			}

			std::sort(indices.rbegin(), indices.rend());
			for (int index : indices) {
				hand_.push_back(deck_[index]); // hand_ に追加
				deck_.erase(deck_.begin() + index); // deck_ から削除
			}
		}
	}
}

ScoreData Deck::GetChangedScoreData(ScoreData* scoreData, int maxScore, float rate) {
	//スキル使用後予想
	ScoreData changedScoreData;
	changedScoreData.score = 0;
	ScoreData scoredata = GetSelectedSkill().GetScoreData();

	//体力計算
	if (scoreData->shield >= scoredata.cost) {
		changedScoreData.shield = -scoredata.cost;
	}
	else {
		changedScoreData.shield = -scoreData->shield;
		scoredata.cost -= scoreData->shield;
	}

	//スコア計算
	if (scoredata.score > 0) {
		int newScore = 0;
		if (scoreData->condition > 0) {
			float addScore = static_cast<float>(scoredata.score + scoreData->concentration) * 1.5f;
			changedScoreData.score += static_cast<int>(ceil(addScore * rate));
		}
		else {
			changedScoreData.score += static_cast<int>(ceil((scoredata.score + scoreData->concentration) * rate));
		}

		if (GetSelectedSkill().name_ == "twice") {
			if (scoreData->condition > 0) {
				float addScore = static_cast<float>(scoredata.score + scoreData->concentration) * 1.5f;
				changedScoreData.score += static_cast<int>(ceil(addScore * rate));
			}
			else {
				changedScoreData.score += static_cast<int>(ceil((scoredata.score + scoreData->concentration) * rate));
			}
		}

		newScore = scoreData->score + changedScoreData.score;
		if (maxScore > 0) {
			if (maxScore < newScore) {
				changedScoreData.score = maxScore - scoreData->score;
			}
		}
	}

	//バフ追加
	changedScoreData.concentration = scoredata.concentration;
	changedScoreData.condition = scoredata.condition;
	changedScoreData.shield += scoredata.shield;

	return changedScoreData;
}

int Deck::GetChangedHp(ScoreData* scoreData) {
	//スキル使用後予想
	ScoreData changedScoreData;
	ScoreData scoredata = GetSelectedSkill().GetScoreData();

	//体力計算
	if (scoreData->shield < scoredata.cost) {
		changedScoreData.shield = -scoreData->shield;
		scoredata.cost -= scoreData->shield;
		return scoredata.cost;
	}
	return 0;
}

void Deck::UseSkill(ScoreData* scoreData, int* hp, int maxScore, float rate) {
	Input* input = Input::GetInstance();

	for (int i = 0; i < 3; i++) {
		canUseSkill_[i] = hand_[i].CanUseSkill(scoreData, *hp);
	}

	//実行
	if (input->TriggerKey(DIK_Q) && canUseSkill_[0]) {
		if (selectedSkillNum_ == 0) {
			usedSkill_ = hand_[0];
			usedSkill_.Use(scoreData, hp, maxScore, rate);
			isUsedSkill_ = true;
			if (hand_[0].isOneTime_ == true) {
				banish_.push_back(hand_[0]);
				hand_.erase(hand_.begin());
			}
			handPos_[0].y = defaultHandPos_[0].y;
			selectedSkillNum_ = -1;
			isSelectedSkill_ = false;
			Discard();
			DrawSkill();
		}
		else {
			isSelectedSkill_ = true;
			selectedSkill_ = hand_[0];
			selectedSkillNum_ = 0;
			handPos_[0].y = defaultHandPos_[0].y + addSelecthandPos_;
			handPos_[1].y = defaultHandPos_[1].y;
			handPos_[2].y = defaultHandPos_[2].y;
		}
	}
	else if (input->TriggerKey(DIK_W) && canUseSkill_[1]) {
		if (selectedSkillNum_ == 1) {
			usedSkill_ = hand_[1];
			usedSkill_.Use(scoreData, hp, maxScore, rate);
			isUsedSkill_ = true;
			if (hand_[1].isOneTime_ == true) {
				banish_.push_back(hand_[1]);
				hand_.erase(hand_.begin() + 1);
			}
			handPos_[1].y = defaultHandPos_[1].y;
			selectedSkillNum_ = -1;
			isSelectedSkill_ = false;
			Discard();
			DrawSkill();
		}
		else {
			isSelectedSkill_ = true;
			selectedSkillNum_ = 1;
			selectedSkill_ = hand_[1];
			handPos_[0].y = defaultHandPos_[0].y;
			handPos_[1].y = defaultHandPos_[1].y + addSelecthandPos_;
			handPos_[2].y = defaultHandPos_[2].y;
		}
	}
	else if (input->TriggerKey(DIK_E) && canUseSkill_[2]) {
		if (selectedSkillNum_ == 2) {
			usedSkill_ = hand_[2];
			usedSkill_.Use(scoreData, hp, maxScore, rate);
			isUsedSkill_ = true;
			if (hand_[2].isOneTime_ == true) {
				banish_.push_back(hand_[2]);
				hand_.erase(hand_.begin() + 2);
			}
			handPos_[2].y = defaultHandPos_[2].y;
			selectedSkillNum_ = -1;
			isSelectedSkill_ = false;
			Discard();
			DrawSkill();
		}
		else {
			isSelectedSkill_ = true;
			selectedSkill_ = hand_[2];
			selectedSkillNum_ = 2;
			handPos_[0].y = defaultHandPos_[0].y;
			handPos_[1].y = defaultHandPos_[1].y;
			handPos_[2].y = defaultHandPos_[2].y + addSelecthandPos_;
		}
	}
}

void Deck::Discard() {
	selectedSkillNum_ = -1;
	isSelectedSkill_ = false;
	handPos_[0].y = defaultHandPos_[0].y;
	handPos_[1].y = defaultHandPos_[1].y;
	handPos_[2].y = defaultHandPos_[2].y;
	discard_.insert(discard_.end(), hand_.begin(), hand_.end());
	hand_.clear();
}

void Deck::Shuffle() {
	mt19937_64 get_rand_mt(0);
	shuffle(deck_.begin(), deck_.end(), get_rand_mt);
}

void Deck::ResetDeck() {
	deck_.clear();
	SetDeck();
	Shuffle();
	hand_.clear();
	discard_.clear();
	banish_.clear();
	DrawSkill();
}

void Deck::SpriteSort() {
	//hand
	if (hand_.size() == 3) {
		hand_[0].sprite_.SetPozition(handPos_[0]);
		hand_[0].sprite_.Update();
		hand_[1].sprite_.SetPozition(handPos_[1]);
		hand_[1].sprite_.Update();
		hand_[2].sprite_.SetPozition(handPos_[2]);
		hand_[2].sprite_.Update();
	}

	//deck
	for (int i = 0; i < deck_.size(); i++) {
		deck_[i].sprite_.SetPozition({ i % 4 * 80.0f + 900,i / 4 * 80.0f + 70 });
		deck_[i].sprite_.Update();
	}

	//discard
	for (int i = 0; i < discard_.size(); i++) {
		discard_[i].sprite_.SetPozition({ i % 4 * 80.0f + 900,i / 4 * 80.0f + 370 });
		discard_[i].sprite_.Update();
	}

	//banish
	for (int i = 0; i < banish_.size(); i++) {
		banish_[i].sprite_.SetPozition({ i % 4 * 80.0f + 900,i / 4 * 80.0f + 630 });
		banish_[i].sprite_.Update();
	}
}

void Deck::DrawHand() {
	handSprite_.Draw();
	if (hand_.size() == 3) {
		for (int i = 0; i < 3; i++) {
			hand_[i].sprite_.Draw();
		}
	}
}

void Deck::DrawList() {
	deckSprite_.Draw();
	for (int i = 0; i < deck_.size(); i++) {
		deck_[i].sprite_.Draw();
	}

	discardSprite_.Draw();
	for (int i = 0; i < discard_.size(); i++) {
		discard_[i].sprite_.Draw();
	}

	banishSprite_.Draw();
	for (int i = 0; i < banish_.size(); i++) {
		banish_[i].sprite_.Draw();
	}
}

void Deck::DrawDeck() {
	for (int i = 0; i < hasSkills_.size(); i++) {
		hasSkills_[i].sprite_.Draw();
	}
}

void Deck::DrawAddSkill() {
	for (int i = 0; i < 3; i++) {
		addRandList_[i].sprite_.Draw();
	}
}