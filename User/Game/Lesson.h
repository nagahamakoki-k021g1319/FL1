#pragma once
#include"Player.h"
#include "HpShieldUI.h"
#include "BufUI.h"
#include "Audio.h"

class Lesson{
public:
	void Initialize(int maxTurn, int perfectScore, int type);
	void Update();
	void Draw();

	void SetPlayer(Player* player);

	bool GetIsLessonEnd() { return isLessonEnd_; };
private:
	Player* player_;

	int type_;
	int maxTurn_;
	int turn_;
	std::unique_ptr<Number>	turnNumber_;
	std::unique_ptr<Number>	borderScoreNumber_;
	std::unique_ptr<Sprite> clearScorePing_;
	std::unique_ptr<Sprite> perfectScorePing_;
	std::unique_ptr<Sprite> remainingTurnPing_;
	std::unique_ptr<Sprite> explanationPing_;

	unique_ptr<HpShieldUI> hpShieldUI_ = nullptr;
	unique_ptr<BufUI> bufUI_ = nullptr;

	Audio* audio_ = nullptr;
	IXAudio2SourceVoice* pSourceVoice_;

	int clearScore_;
	int perfectScore_;

	bool isLoopEnd_;
	bool isLessonEnd_;

	bool isBGMStart = false;
};

