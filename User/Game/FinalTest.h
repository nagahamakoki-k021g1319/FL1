#pragma once
#include"Player.h"
#include "HpShieldUI.h"
#include "BufUI.h"

class FinalTest
{
public:

	void Initialize();

	void SetPlayer(Player* player);

	bool GetIsLessonEnd() { return isLessonEnd_; };

	void Update();

	void Draw();

	void ApplyGlobalVariables();

	void Calculation(Vector3 status, int point);
	int CalculationState(int num);
	int CalculationRequiredScore(int score);



private:
	Player* player_;

	int type_;
	int maxTurn_;
	int turn_;
	int turnType[12];
	
	Vector3 statusCorrection_;
	float statusRate_[3];
	std::unique_ptr<Number>	statusRateNumber_[3];

	std::unique_ptr<Number>	turnNumber_;
	std::unique_ptr<Sprite> remainingTurnPing_;
	std::unique_ptr<Sprite> explanationPing_;

	unique_ptr<HpShieldUI> hpShieldUI_ = nullptr;
	//unique_ptr<BufUI> bufUI_ = nullptr;

	bool isLoopEnd_;
	bool isLessonEnd_;

	int border[7] = { 3000,4500,6000,8000,10000,11500,13000};
	int maxState = 1800;
	int pointSeparator[5] = { 5000,10000,20000,30000,40000, };

	int evaluationValue_ = 0;
	int clearRank_ = 0;
	std::unique_ptr<Number>	evaluationValueNumber_;
	std::unique_ptr<Sprite> clearRankPing_;
};
