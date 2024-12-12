#include"Deck.h"
#include <random>
#include <algorithm>
#include"Input.h"

void Deck::Initilize(Skills skills) {
	AddSkill(skills,"appeal");
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

void Deck::SetDeck() {
	copy(hasSkills_.begin(), hasSkills_.end(), back_inserter(deck_));
}

void Deck::Update() {


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

		if (deckNum >= drawNum) {
			copy(deck_.begin(), deck_.begin() + drawNum, back_inserter(hand_));
			deck_.erase(deck_.begin(), deck_.begin() + drawNum);

		}
		else {
			copy(deck_.begin(), deck_.begin() + deckNum, back_inserter(hand_));
			deck_.erase(deck_.begin(), deck_.begin() + deckNum);

			copy(discard_.begin(), discard_.end(), back_inserter(deck_));
			discard_.clear();
			Shuffle();

			copy(deck_.begin(), deck_.begin() + (drawNum - deckNum), back_inserter(hand_));
			deck_.erase(deck_.begin(), deck_.begin() + (drawNum - deckNum));
		}
	}
}

void Deck::UseSkill(ScoreData scoreData, int hp) {
	Input* input = Input::GetInstance();

	for (int i=0; i < 3; i++) {
		canUseSkill_[i] = hand_[i].CanUseSkill(scoreData, hp);
	}

	//実行
	if (input->TriggerKey(DIK_Q) && canUseSkill_[0]) {
		if (selectedSkillNum_ == 0) {
			usedSkill_ = hand_[0];
			isUsedSkill_ = true;
			if (hand_[0].isOneTime_ == true) {
				banish_.push_back(hand_[0]);
				hand_.erase(hand_.begin());
			}
			handPos_[0].y = defaultHandPos_[0].y;
			selectedSkillNum_ = -1;
			isSelectedSkill_ = false;
			Discard();
		}else {
			isSelectedSkill_ = true;
			selectedSkill_ = hand_[0];
			selectedSkillNum_ = 0;
			handPos_[0].y = defaultHandPos_[0].y + addSelecthandPos_;
			handPos_[1].y = defaultHandPos_[1].y;
			handPos_[2].y = defaultHandPos_[2].y;
		}
	}else if (input->TriggerKey(DIK_W) && canUseSkill_[1]) {
		if (selectedSkillNum_ == 1) {
			usedSkill_ = hand_[1];
			isUsedSkill_ = true;
			if (hand_[1].isOneTime_ == true) {
				banish_.push_back(hand_[1]);
				hand_.erase(hand_.begin() + 1);
			}
			handPos_[1].y = defaultHandPos_[1].y;
			selectedSkillNum_ = -1;
			isSelectedSkill_ = false;
			Discard();
		}else {
			isSelectedSkill_ = true;
			selectedSkillNum_ = 1;
			selectedSkill_ = hand_[1];
			handPos_[0].y = defaultHandPos_[0].y;
			handPos_[1].y = defaultHandPos_[1].y + addSelecthandPos_;
			handPos_[2].y = defaultHandPos_[2].y;
		}
	}else if (input->TriggerKey(DIK_E) && canUseSkill_[2]) {
		if (selectedSkillNum_ == 2) {
			usedSkill_ = hand_[2];
			isUsedSkill_ = true;
			if (hand_[2].isOneTime_ == true) {
				banish_.push_back(hand_[2]);
				hand_.erase(hand_.begin() + 2);
			}
			handPos_[2].y = defaultHandPos_[2].y;
			selectedSkillNum_ = -1;
			isSelectedSkill_ = false;
			Discard();
		}else {
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