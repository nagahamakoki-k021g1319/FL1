#include "Number.h"

Number::Number()
{
}

Number::~Number()
{
}

void Number::Initialize() {
	drawSize_ = { 32,64 };
	for (int i = 0; i < 5; i++) {
		sprite_[i].Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex("nums.png"));
		sprite_[i].SetSize(drawSize_);
	}
}

void Number::Draw(const Vector2& pos, size_t num, float scl){
	size_t digit = 0;
	size_t calculatedNum = num;
	while (calculatedNum != 0){
		calculatedNum /= 10;
		digit++;
	}

	size_t div = 1;

	for (size_t i = 0; i < digit; i++)
	{
		int32_t n = num / div % 10;
		
		sprite_[i].SetPozition({pos.x + (digit - i) * (drawSize_.x * scl), pos.y});
		sprite_[i].SetTexLeftTop({32.0f * static_cast<float>(n), 0});
		sprite_[i].SetTexSize({ 32.0f, 64.0f});
		sprite_[i].SetSize({ drawSize_.x * scl, drawSize_.y * scl });
		sprite_[i].Update();

		sprite_[i].Draw();

		div *= 10;
	}
}
