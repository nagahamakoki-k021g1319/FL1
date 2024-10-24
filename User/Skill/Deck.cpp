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
}

void Deck::AddSkill(Skills skills, std::string name) {
	Skills::Skill newSkill = skills.GetSkill(name);
	newSkill.sprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex(newSkill.name_ + ".png"));
	newSkill.sprite_.SetSize({ 64,64 });
	hasSkills_.push_back(newSkill);
}

void Deck::SetDeck() {
	copy(hasSkills_.begin(), hasSkills_.end(), back_inserter(deck_));
}

void Deck::Update() {


}

void Deck::DrawSkill() {
	int drawNum = 3;
	std::size_t deckNum = deck_.size();

	if (deckNum >= drawNum) {
		copy(deck_.begin(), deck_.begin() + drawNum, back_inserter(hand_));
		deck_.erase(deck_.begin(), deck_.begin() + drawNum);

	}else {
		copy(deck_.begin(), deck_.begin() + deckNum, back_inserter(hand_));
		deck_.erase(deck_.begin(), deck_.begin() + deckNum);

		copy(discard_.begin(), discard_.end(), back_inserter(deck_));
		discard_.clear();
		Shuffle();

		copy(deck_.begin(), deck_.begin() + (drawNum - deckNum), back_inserter(hand_));
		deck_.erase(deck_.begin(), deck_.begin() + (drawNum - deckNum));
	}
}

void Deck::UseSkill() {
	if (Input::GetInstance()->TriggerKey(DIK_Z)) {
		usedSkill_ = hand_[0];
		if (hand_[0].isOneTime_ == true) {
			banish_.push_back(hand_[0]);
			hand_.erase(hand_.begin());
		}
		Discard();
	}else if (Input::GetInstance()->TriggerKey(DIK_X)) {
		usedSkill_ = hand_[1]; if (hand_[1].isOneTime_ == true) {
			banish_.push_back(hand_[1]);
			hand_.erase(hand_.begin() + 1);
		}
		Discard();
	}else if (Input::GetInstance()->TriggerKey(DIK_C)) {
		usedSkill_ = hand_[2]; if (hand_[2].isOneTime_ == true) {
			banish_.push_back(hand_[2]);
			hand_.erase(hand_.begin() + 2);
		}
		Discard();
	}
}

void Deck::Discard() {
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
		hand_[0].sprite_.SetPozition({ 440,500 });
		hand_[0].sprite_.Update();
		hand_[1].sprite_.SetPozition({ 540,500 });
		hand_[1].sprite_.Update();
		hand_[2].sprite_.SetPozition({ 640,500 });
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