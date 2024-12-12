#pragma once
#include "Lesson.h"
#include "Consult.h"
#include "FinalTest.h"

#include"Player.h"
#include "Game/Lesson.h"

#include "HpShieldUI.h"
#include "BufUI.h"

class GameFlow{
public:
	void Initialize();

	void Update();

	void Draw();

	void ApplyGlobalVariables();

private:
	Player player_;

	unique_ptr<HpShieldUI> hpShieldUI_ = nullptr;
	unique_ptr<BufUI> bufUI_ = nullptr;
	
	unique_ptr<Lesson> lesson_ = nullptr;
};

