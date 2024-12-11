#pragma once
#include "Affin.h"
#include "Easing.h"
#include "Vector2.h"
#include <vector>
#include "Sprite.h"

class Bar
{
public:
	Bar();
	~Bar();

	void Initialize(Vector2 minMax);
	void Update();
	void Draw();
	void ONDraw() { isDraw = true; };
	void OFFDraw() { isDraw = false; };

private:
	float maxBarSize_;
	float minBarSize_;
	Sprite sprite_;
	bool isDraw;
private:

};


class BarGraph
{
public:
	BarGraph();
	~BarGraph();

	void Initialize();
	void Update();
	void Draw();
	void SetDivision(uint32_t div) { division_ = div; }
	void NowProgres(uint32_t num) { progress = num; }
	

private:
	float maxSize_ = 800;
	float minSize_ = 0;
	uint32_t progress;
	uint32_t params_;
	uint32_t division_;
	std::vector<Bar> bars_;
private:
	
};


