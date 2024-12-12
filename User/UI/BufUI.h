#pragma once
#include "Sprite.h"
#include "BarGraph.h"
#include "Number.h"
#include <memory>

using namespace std;


class BufUI
{
public:
	BufUI();
	~BufUI();

	void Initialize();
	void Update();
	void Draw();

private:
	unique_ptr<Sprite>	qSprite_;
	unique_ptr<Sprite>	wSprite_;
	unique_ptr<Sprite>	eSprite_;
	unique_ptr<Sprite>	sSprite_;
};

