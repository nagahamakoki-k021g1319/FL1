#include "BarGraph.h"
#include "SpriteLoader.h"
#include "Easing.h"

BlockGraph::BlockGraph()
{

}

BlockGraph::~BlockGraph()
{

}

void BlockGraph::Initialize()
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

void BlockGraph::Update()
{
	for (size_t i = 0; i < bars_.size(); i++) {
		if (i < progress) {
			bars_[i].ONDraw();
		}
		else {
			bars_[i].OFFDraw();
		}
	}
	for (Block bar : bars_) {
		bar.Update();
	}
}

void BlockGraph::Draw()
{
	for (Block bar : bars_) {
		bar.Draw();
	}
}

Block::Block()
{

}

Block::~Block()
{

}

void Block::Initialize(Vector2 minMax)
{
	minBarSize_ = minMax.x;
	maxBarSize_ = minMax.y;
	sprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("white.png"));
	sprite_.SetPozition({ startPos_.x + minMax.x,startPos_.y });
	sprite_.SetSize({ 60, 30 });
	//sprite_.SetSize({ MyEngine::Easing::lerpFloat(minBarSize_,maxBarSize_,0.5f), 30 });
}

void Block::Update()
{
	//sprite_.SetSize({ MyEngine::Easing::lerpFloat(minBarSize_,maxBarSize_,0.5f), 30});
	sprite_.Update();
}

void Block::Draw()
{
	if (isDraw) {
		sprite_.Draw();
	}
	else {

	}
}

BarGraph::BarGraph()
{
}

BarGraph::~BarGraph()
{
}

void BarGraph::Initialize(Vector2 startPos, const std::string& spriteName)
{
	startPos_ = startPos;
	isDraw = true;
	sprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex(spriteName));
	sprite_.SetPozition({ startPos_.x ,startPos_.y });
	sprite_.SetSize({ 0, size_.y });
	//sprite_.SetSize({ MyEngine::Easing::lerpFloat(minBarSize_,maxBarSize_,0.5f), 30 });
}

void BarGraph::Update()
{
	//sprite_.SetSize({ MyEngine::Easing::lerpFloat(minBarSize_,maxBarSize_,0.5f), 30});
	//sprite_.SetPozition({ startPos_.x ,startPos_.y });
	if (paramsUpdate_) {
		sprite_.SetSize({ (float)params_ * size_.x, size_.y });
	}
	sprite_.Update();
}

void BarGraph::Draw()
{
	if (isDraw) {
		sprite_.Draw();
	}
	else {

	}
}

void BarGraph::EaseParms(float startParams, float endParams, float time)
{
	if (time > 0) {
		paramsUpdate_ = true;
		params_ = MyEngine::Easing::lerpFloat(startParams, endParams, time);
	}
	else {
		paramsUpdate_ = false;
	}
}

void BarGraph::AutoEaseParms(float& oldParams, float newParams){

	if (params_ != newParams) {
		timeStart = true;
	}
	else {
		timeStart = false;
	}

	if (timeStart) {
		if (count <= easeMaxCount) {
			count++;
		}
		else {
			count = easeMaxCount;
			params_ = newParams;
			oldParams = params_;
		}
		easetime = (float)count / (float)easeMaxCount;
		EaseParms((float)oldParams, (float)newParams, easetime);
	}
	else {
		count = 0;
		easetime = 0;
		params_ = newParams;
		oldParams = params_;
	}
}