#pragma once
#include "Affin.h"
#include "Easing.h"
#include "Vector2.h"
#include <vector>
#include "Sprite.h"
#include "ImGuiManager.h"

class Block
{
public:
	Block();
	~Block();

	void Initialize(Vector2 minMax);
	void Update();
	void Draw();
	void ONDraw() { isDraw = true; };
	void OFFDraw() { isDraw = false; };
	void SetStartPos(Vector2 startPos) { startPos_ = startPos; }

private:
	float maxBarSize_;
	float minBarSize_;
	Sprite sprite_;
	bool isDraw;
	Vector2 startPos_;
private:

};


class BlockGraph
{
public:
	BlockGraph();
	~BlockGraph();

	void Initialize();
	void Update();
	void Draw();
	void SetDivision(uint32_t div) { division_ = div; }
	void NowProgres(uint32_t num) { progress = num; }
	void SetStartPos(Vector2 startPos) { startPos_ = startPos; }

private:
	Vector2 startPos_;
	float maxSize_ = 800;
	float minSize_ = 0;
	uint32_t progress;
	uint32_t params_;
	uint32_t division_;
	std::vector<Block> bars_;
private:

};

class BarGraph
{
public:
	BarGraph();
	~BarGraph();

	void Initialize(Vector2 startPos,const std::string& spriteName = "white.png");
	void Update();
	void Draw();
	void SetDivision(uint32_t div) { division_ = div; }
	void SetHP(uint32_t HP) { HP_ = HP; }
	void SetParams(uint32_t params) { params_ = params; }
	void SetStartPos(Vector2 startPos) { startPos_ = startPos; }
	void SetSize(Vector2 size) { size_ = size; }

private:
	Vector2 startPos_;
	Vector2 size_ = { 8.0f,30.0f };
	uint32_t HP_;
	uint32_t params_=100;
	uint32_t division_;
private:
	Sprite sprite_;
	bool isDraw;
};

