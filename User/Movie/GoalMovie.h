#pragma once
#include "BaseMovie.h"
class GoalMovie : public BaseMovie
{
public:
	GoalMovie();

	void Init() override;

	void Update(TGameCamera* camera) override;
};

