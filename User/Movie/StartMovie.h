#pragma once
#include "BaseMovie.h"
class StartMovie : public BaseMovie {
public:
	StartMovie();

	void Init() override;

	void Update(TGameCamera* camera) override;

private:

};
