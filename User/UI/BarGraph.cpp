#include "BarGraph.h"
#include "SpriteLoader.h"
#include "Easing.h"

BarGraph::BarGraph()
{

}

BarGraph::~BarGraph()
{

}

void BarGraph::Initialize()
{
	float minSize = 0;
	float maxSize = 0;
	float diff = 0;
	diff = (float)maxSize_ / (float)division_;
	maxSize = diff;
	bars_.resize(division_);
	for (size_t i = 0; i < bars_.size(); i++) {
		bars_[i].SetStartPos(startPos_);
		bars_[i].Initialize({ minSize,maxSize });
		minSize = maxSize;
		maxSize += diff;
	}
}

void BarGraph::Update()
{
	for (size_t i = 0; i < bars_.size(); i++) {
		if (i < progress) {
			bars_[i].ONDraw();
		}
		else {
			bars_[i].OFFDraw();
		}
	}
	for (Bar bar : bars_) {
		bar.Update();
	}
}

void BarGraph::Draw()
{
	for (Bar bar : bars_) {
		bar.Draw();
	}
}

Bar::Bar()
{

}

Bar::~Bar()
{

}

void Bar::Initialize(Vector2 minMax)
{
	minBarSize_ = minMax.x;
	maxBarSize_ = minMax.y;
	sprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("white.png"));
	sprite_.SetPozition({startPos_.x + minMax.x,startPos_.y });
	sprite_.SetSize({ 60, 30 });
	//sprite_.SetSize({ MyEngine::Easing::lerpFloat(minBarSize_,maxBarSize_,0.5f), 30 });
}

void Bar::Update()
{
	//sprite_.SetSize({ MyEngine::Easing::lerpFloat(minBarSize_,maxBarSize_,0.5f), 30});
	sprite_.Update();
}

void Bar::Draw()
{
	if (isDraw) {
		sprite_.Draw();
	}
	else {

	}
}
