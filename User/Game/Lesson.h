#pragma once
#include"Player.h"

class Lesson{
public:
	void Initialize(int maxTurn, int clearScore,int perfectScore,int type);
	void Update();
	void Draw();

	void SetPlayer(Player* player) { player_ = player; };

	bool GetIsLessonEnd() { return isLessonEnd_; };
private:
	Player* player_;

	int type_;
	int maxTurn_;
	int turn_;
	std::unique_ptr<Number>	turnNumber_;
	std::unique_ptr<Sprite> remainingTurnPing_;

	int clearScore_;
	int perfectScore_;

	bool isLoopEnd_;
	bool isLessonEnd_;
};

