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
	AddSkill(skills, "behavior");
	AddSkill(skills, "highFive");
	AddSkill(skills, "highFive");

	SetDeck();
	Shuffle();

	deckBackSprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("deckBack.png"));
	deckBackSprite_.SetPozition({ 895,0 });
	deckSprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("deck.png"));
	deckSprite_.SetPozition({ 920,10 });
	discardSprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("discard.png"));
	discardSprite_.SetPozition({ 920,300 });
	banishSprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("banish.png"));
	banishSprite_.SetPozition({ 920,590 });

	addSelecthandPos_ = -20;
	defaultHandPos_[0] = { 530,572 };
	defaultHandPos_[1] = { 640,572 };
	defaultHandPos_[2] = { 750,572 };
	handPos_[0] = defaultHandPos_[0];
	handPos_[1] = defaultHandPos_[1];
	handPos_[2] = defaultHandPos_[2];
	isUsedSkill_ = false;
	isSelectedSkill_ = false;
	selectedSkillNum_ = -1;

	audio_ = new Audio();
	audio_->Initialize();
	audio_->LoadWave("cursorMove.wav");

	audio2_ = new Audio();
	audio2_->Initialize();
	audio2_->LoadWave("cursorClick.wav");

  skipButton_.Initialize("s", { 830,470 });
	reloadButton_.Initialize("reload", { 790,650 });
	reloadNum_ = 3;
	reloadNumber_.Initialize();
}

void Deck::AddSkill(Skills skills, std::string name) {
	Skill newSkill = skills.GetSkill(name);
	newSkill.button_.Initialize(newSkill.name_);
	newSkill.button_.SetSize({ 64,64 });
	newSkill.explanation_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex(name + "txt.png"));
	newSkill.explanation_.SetAnchorPoint({ 0.5f,0.5f });
	newSkill.explanation_.SetPozition({ 640,430 });
	hasSkills_.push_back(newSkill);
}

void Deck::AddRandSkillDraw(Skills skills) {
	const int skillNum = 9;
	string skillName[skillNum];
	skillName[0] = "step";
	skillName[1] = "warmUp";
	skillName[2] = "fanService";
	skillName[3] = "talkTime";
	skillName[4] = "stubborn";
	skillName[5] = "sign";
	skillName[6] = "will";
	skillName[7] = "breath";
	skillName[8] = "highFive";

	addRandList_.clear();

	std::set<int> uniqueNumbers;
	while (uniqueNumbers.size() < 3) {
		int number = rand() % skillNum;//スキルカードの種類数
		uniqueNumbers.insert(number);
	}


	for (int i = 0; i < 3; i++) {
		auto it = uniqueNumbers.begin();
		std::advance(it, i);
		Skill newSkill = skills.GetSkill(skillName[*it]);
		newSkill.button_.Initialize(newSkill.name_, { 530.0f + 110.0f * static_cast<float>(i),572 });
		newSkill.button_.SetSize({ 84,84 });
		newSkill.explanation_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex(newSkill.name_ + "txt.png"));//変更予定箇所
		newSkill.explanation_.SetAnchorPoint({ 0.5f,0.5f });
		newSkill.explanation_.SetPozition({ 640,430 });
		addRandList_.push_back(newSkill);
	}
}

bool Deck::AddRandSkill() {
	
	for (int i = 0; i < addRandList_.size(); i++) {
		addRandList_[i].button_.Update();
	}

	if (addRandList_[0].button_.IsMouseClick()) {
		if (addRandList_[0].isSelected_ == true) {
			hasSkills_.push_back(addRandList_[0]);
			return true;
		}else {
			addRandList_[0].isSelected_ = true;
			addRandList_[0].button_.SetPosition({ defaultHandPos_[0].x,defaultHandPos_[0].y + addSelecthandPos_ });
			addRandList_[1].isSelected_ = false;
			addRandList_[1].button_.SetPosition({ defaultHandPos_[1].x,defaultHandPos_[1].y});
			addRandList_[2].isSelected_ = false;
			addRandList_[2].button_.SetPosition({ defaultHandPos_[2].x,defaultHandPos_[2].y});
			return false;
		}
	}else if (addRandList_[1].button_.IsMouseClick()) {
		if (addRandList_[1].isSelected_ == true) {
			hasSkills_.push_back(addRandList_[1]);
			return true;
		}else {
			addRandList_[0].isSelected_ = false;
			addRandList_[0].button_.SetPosition({ defaultHandPos_[0].x,defaultHandPos_[0].y});
			addRandList_[1].isSelected_ = true;
			addRandList_[1].button_.SetPosition({ defaultHandPos_[1].x,defaultHandPos_[1].y + addSelecthandPos_ });
			addRandList_[2].isSelected_ = false;
			addRandList_[2].button_.SetPosition({ defaultHandPos_[2].x,defaultHandPos_[2].y});
			return false;
		}
	}else if (addRandList_[2].button_.IsMouseClick()) {
		if (addRandList_[2].isSelected_ == true) {
			hasSkills_.push_back(addRandList_[2]);
			return true;
		}else {
			addRandList_[0].isSelected_ = false;
			addRandList_[0].button_.SetPosition({ defaultHandPos_[0].x,defaultHandPos_[0].y});
			addRandList_[1].isSelected_ = false;
			addRandList_[1].button_.SetPosition({ defaultHandPos_[1].x,defaultHandPos_[1].y});
			addRandList_[2].isSelected_ = true;
			addRandList_[2].button_.SetPosition({ defaultHandPos_[2].x,defaultHandPos_[2].y + addSelecthandPos_});
			return false;
		}
	}


	//スキル獲得スキップ
	//else if (Input::GetInstance()->TriggerKey(DIK_S)) {
	//	return true;
	//}

	return false;
}

bool Deck::IsReloard() {
	if (reloadNum_ > 0) {
		reloadButton_.Update();
		if (reloadButton_.IsMouseClick()) {
			reloadNum_--;
			return true;
		}
	}
	return false;
}

void Deck::SetDeck() {
	copy(hasSkills_.begin(), hasSkills_.end(), back_inserter(deck_));
}

void Deck::Update(ScoreData* scoreData, int* hp, int maxScore, float rate) {
	//どこかでクリック時一度全部解除
	if (Input::GetInstance()->TriggerMouse(0)) {
		bool select[3] = { false,false,false };
		for (int i = 0; i < hand_.size(); i++) {
			hand_[i].button_.Update();
			if (hand_[i].button_.IsMouseClick()) {
				hand_[i].isSelected_ = true;
				select[i] = true;
				//スキル選択時サウンド鳴らす
				pSourceVoice_ = audio_->PlayWave("cursorMove.wav");
			}else {
				hand_[i].isSelected_ = false;
			}
		}
		if (select[0] == false && select[1] == false && select[2] == false) {
			selectedSkillNum_ = -1;
		}

		for (int i = 0; i < deck_.size(); i++) {
			deck_[i].button_.Update();
			if (deck_[i].button_.IsMouseClick()) {
				deck_[i].isSelected_ = true;
				//スキル選択時サウンド鳴らす
				pSourceVoice_ = audio_->PlayWave("cursorMove.wav");
			}else {
				deck_[i].isSelected_ = false;
			}
		}
		for (int i = 0; i < discard_.size(); i++) {
			discard_[i].button_.Update();
			if (discard_[i].button_.IsMouseClick()) {
				discard_[i].isSelected_ = true;
				//スキル選択時サウンド鳴らす
				pSourceVoice_ = audio_->PlayWave("cursorMove.wav");
			}else {
				discard_[i].isSelected_ = false;
			}
		}
		for (int i = 0; i < banish_.size(); i++) {
			banish_[i].button_.Update();
			if (banish_[i].button_.IsMouseClick()) {
				banish_[i].isSelected_ = true;
				//スキル選択時サウンド鳴らす
				pSourceVoice_ = audio_->PlayWave("cursorMove.wav");
			}else {
				banish_[i].isSelected_ = false;
			}
		}
	}
	for (int i = 0; i < hand_.size(); i++) {
		hand_[i].button_.Update();
	}
	for (int i = 0; i < deck_.size(); i++) {
		deck_[i].button_.Update();
	}
	for (int i = 0; i < discard_.size(); i++) {
		discard_[i].button_.Update();
	}
	for (int i = 0; i < banish_.size(); i++) {
		banish_[i].button_.Update();
	}
		
	skipButton_.Update();

	UseSkill(scoreData, hp, maxScore,rate);

	//スキップ
	if (skipButton_.IsMouseClick()) {
		*(hp) += 2;
		const int maxHp = 40;
		if (*(hp) > maxHp) {
			*(hp) = maxHp;
		}
		if (scoreData->condition > 0) {
			scoreData->condition--;
		}
		isUsedSkill_ = true;

		for (int i = 0; i < 3; i++) {
			hand_[i].button_.SetSize({ 64,64 });
		}

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

void Deck::FirstDrawSkill() {
	int num = 0;
	hand_.clear();
	for (auto it = deck_.begin(); it != deck_.end();) {
		if (it->name_ == "will") {
			it->button_.SetSize({84,84});
			hand_.push_back(*it);  // hand_ に追加
			it = deck_.erase(it);  // deck_ から削除
			num++;
		}
		else {
			++it; // 削除しなかった場合は次へ
		}
	}
	std::vector<int> indices;
	while (indices.size() < 3 - num) {
		int randIndex = rand() % deck_.size();
		if (std::find(indices.begin(), indices.end(), randIndex) == indices.end()) {
			indices.push_back(randIndex);
		}
	}
	std::sort(indices.rbegin(), indices.rend());
	for (int index : indices) {
		deck_[index].button_.SetSize({ 84,84 });
		hand_.push_back(deck_[index]); // hand_ に追加
		deck_.erase(deck_.begin() + index); // deck_ から削除
	}
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
				deck_[index].button_.SetSize({ 84,84 });
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
				deck_[index].button_.SetSize({ 84,84 });
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
				deck_[index].button_.SetSize({ 84,84 });
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
			float addScore = 0;
			if (GetSelectedSkill().name_ == "highFive") {
				addScore = static_cast<float>(scoredata.score + (scoreData->concentration * 2)) * 1.5f;
			}else {
				addScore = static_cast<float>(scoredata.score + scoreData->concentration) * 1.5f;
			}
			changedScoreData.score += static_cast<int>(ceil(addScore * rate));
		}
		else {
			if (GetSelectedSkill().name_ == "highFive") {
				changedScoreData.score += static_cast<int>(ceil((scoredata.score + (scoreData->concentration * 2)) * rate));
			}else {
				changedScoreData.score += static_cast<int>(ceil((scoredata.score + scoreData->concentration) * rate));
			}
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
	for (int i = 0; i < 3; i++) {
		canUseSkill_[i] = hand_[i].CanUseSkill(scoreData, *hp);
	}

	//実行
	if (hand_[0].button_.IsMouseClick() && canUseSkill_[0]) {
		if (selectedSkillNum_ == 0) {
			//スキル使用時サウンド鳴らす
			pSourceVoice2_ = audio2_->PlayWave("cursorClick.wav");
			usedSkill_ = hand_[0];
			usedSkill_.Use(scoreData, hp, maxScore, rate);
			isUsedSkill_ = true;
			hand_[0].isSelected_ = false;
			for (int i = 0; i < 3; i++) {
				hand_[i].button_.SetSize({ 64,64 });
			}
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
	else if (hand_[1].button_.IsMouseClick() && canUseSkill_[1]) {
		if (selectedSkillNum_ == 1) {
			//スキル使用時サウンド鳴らす
			pSourceVoice2_ = audio2_->PlayWave("cursorClick.wav");
			usedSkill_ = hand_[1];
			usedSkill_.Use(scoreData, hp, maxScore, rate);
			isUsedSkill_ = true;
			hand_[1].isSelected_ = false;
			for (int i = 0; i < 3; i++) {
				hand_[i].button_.SetSize({ 64,64 });
			}
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
	else if (hand_[2].button_.IsMouseClick() && canUseSkill_[2]) {
		if (selectedSkillNum_ == 2) {
			//スキル使用時サウンド鳴らす
			pSourceVoice2_ = audio2_->PlayWave("cursorClick.wav");
			usedSkill_ = hand_[2];
			usedSkill_.Use(scoreData, hp, maxScore, rate);
			isUsedSkill_ = true;
			hand_[2].isSelected_ = false;
			for (int i = 0; i < 3; i++) {
				hand_[i].button_.SetSize({ 64,64 });
			}
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
	for (int i = 0; i < deck_.size();i++) {
		deck_[i].button_.SetSize({ 64,64 });
	}
	FirstDrawSkill();
}

void Deck::SpriteSort() {
	//hand
	if (hand_.size() == 3) {
		hand_[0].button_.SetPosition(handPos_[0]);
		hand_[0].button_.Update();
		hand_[1].button_.SetPosition(handPos_[1]);
		hand_[1].button_.Update();
		hand_[2].button_.SetPosition(handPos_[2]);
		hand_[2].button_.Update();
	}

	//deck
	for (int i = 0; i < deck_.size(); i++) {
		deck_[i].button_.SetPosition({ i % 4 * 80.0f + 967,i / 4 * 80.0f + 92 });
		deck_[i].button_.Update();
	}

	//discard
	for (int i = 0; i < discard_.size(); i++) {
		discard_[i].button_.SetPosition({ i % 4 * 80.0f + 967,i / 4 * 80.0f + 382 });
		discard_[i].button_.Update();
	}

	//banish
	for (int i = 0; i < banish_.size(); i++) {
		banish_[i].button_.SetPosition({ i % 4 * 80.0f + 967,i / 4 * 80.0f + 672 });
		banish_[i].button_.Update();
	}
}

void Deck::DrawHand() {
	if (hand_.size() == 3) {
		for (int i = 0; i < 3; i++) {
			hand_[i].button_.Draw();
			if (hand_[i].isSelected_) {
				hand_[i].explanation_.Draw();
			}
		}
	}
	skipButton_.Draw();
}

void Deck::DrawList() {
	deckBackSprite_.Draw();
	deckSprite_.Draw();
	for (int i = 0; i < deck_.size(); i++) {
		deck_[i].button_.Draw();
		if (deck_[i].isSelected_) {
			deck_[i].explanation_.Draw();
		}
	}

	discardSprite_.Draw();
	for (int i = 0; i < discard_.size(); i++) {
		discard_[i].button_.Draw();
		if (discard_[i].isSelected_) {
			discard_[i].explanation_.Draw();
		}
	}

	banishSprite_.Draw();
	for (int i = 0; i < banish_.size(); i++) {
		banish_[i].button_.Draw();
		if (banish_[i].isSelected_) {
			banish_[i].explanation_.Draw();
		}
	}
}

void Deck::DrawDeck() {
	for (int i = 0; i < hasSkills_.size(); i++) {
		hasSkills_[i].button_.Draw();
	}
}

void Deck::DrawAddSkill() {
	for (int i = 0; i < 3; i++) {
		addRandList_[i].button_.Draw();
		if (addRandList_[i].isSelected_ == true) {
			addRandList_[i].explanation_.Draw();
		}
	}
	reloadButton_.Draw();
	reloadNumber_.Draw({ 783,650 }, reloadNum_, 0.3f);
}