#include"Deck.h"
#include <random>
#include <algorithm>

void Deck::Initilize(Skills skills) {
	hasSkills_.push_back(skills.GetSkill("appeal"));
	//hasSkills_.push_back(skills.GetSkill("appeal"));
	hasSkills_.push_back(skills.GetSkill("pose"));
	hasSkills_.push_back(skills.GetSkill("twice"));
	hasSkills_.push_back(skills.GetSkill("expression"));
	//hasSkills_.push_back(skills.GetSkill("expression"));
	hasSkills_.push_back(skills.GetSkill("face"));
	//hasSkills_.push_back(skills.GetSkill("face"));

	SetDeck();
	Shuffle();
}

void Deck::AddSkill() {

}

void Deck::SetDeck() {
	copy(hasSkills_.begin(), hasSkills_.end(), back_inserter(deck_));
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
	hand_[0].sprite_.SetPozition({ 340,300 });
	hand_[1].sprite_.SetPozition({ 640,300 });
	hand_[2].sprite_.SetPozition({ 940,300 });
	hand_[0].sprite_.Update();
	hand_[1].sprite_.Update();
	hand_[2].sprite_.Update();
}

Skills::Skill Deck::UseSkill() {
	return hand_[0];
}

void Deck::Discard() {
	discard_.insert(discard_.end(), hand_.begin(), hand_.end());
	hand_.clear();
}

void Deck::Shuffle() {
	mt19937_64 get_rand_mt(0);
	shuffle(deck_.begin(), deck_.end(), get_rand_mt);
}

void Deck::DrawHand() {
	if (hand_.size() == 3) {
		hand_[0].sprite_.Draw();
		hand_[1].sprite_.Draw();
		hand_[2].sprite_.Draw();
	}
}