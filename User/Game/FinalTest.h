#pragma once
#include"Player.h"
#include "HpShieldUI.h"
#include "BufUI.h"
#include "Audio.h"

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
	std::unique_ptr<Sprite> turnSchedulePing_;
	std::unique_ptr<Sprite> explanationPing_;
	std::unique_ptr<Sprite> arrowPing_;

	std::unique_ptr<Sprite> voPercentPing_;
	std::unique_ptr<Sprite> daPercentPing_;
	std::unique_ptr<Sprite> viPercentPing_;
	std::unique_ptr<Sprite> voPercentBackPing_;
	std::unique_ptr<Sprite> daPercentBackPing_;
	std::unique_ptr<Sprite> viPercentBackPing_;
	std::unique_ptr<Sprite> voPercentBlackPing_;
	std::unique_ptr<Sprite> daPercentBlackPing_;
	std::unique_ptr<Sprite> viPercentBlackPing_;
	
	unique_ptr<HpShieldUI> hpShieldUI_ = nullptr;
	//unique_ptr<BufUI> bufUI_ = nullptr;

	bool isLoopEnd_;
	bool isLessonEnd_;

	int border[7] = {
		6000,//C
		6500,//C+
		7000,//B
		7500,//B+
		8000,//A
		8500,//A+
		9000//S
	};
	
	int maxState = 1800;
	int pointSeparator[5] = { 5000,10000,20000,30000,40000, };

	int evaluationValue_ = 0;
	int clearRank_ = 0;
	std::unique_ptr<Number>	evaluationValueNumber_;
	std::unique_ptr<Sprite> clearRankPing_;
	std::unique_ptr<Sprite> clearPing_;

	//試験用
	Audio* audio_ = nullptr;
	IXAudio2SourceVoice* pSourceVoice_;
	//評価用
	Audio* audio2_ = nullptr;
	IXAudio2SourceVoice* pSourceVoice2_;

	bool isBGMStart = false;
};
