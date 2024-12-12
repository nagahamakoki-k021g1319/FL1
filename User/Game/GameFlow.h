#pragma once
#include "Lesson.h"
#include "Consult.h"
#include "FinalTest.h"

#include"Player.h"
#include "Game/Lesson.h"

class GameFlow{
public:
	void Initialize();

	void Update();

	void Draw();

	void ApplyGlobalVariables();

private:
	Player player_;
	
	unique_ptr<Lesson> lesson_ = nullptr;
};

