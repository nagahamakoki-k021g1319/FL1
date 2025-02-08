#include"Button.h"
#include"SpriteLoader.h"
#include"Input.h"

void Button::Initialize(std::string spriteName,Vector2 position) {
	isMouseOver = false;
	isMouseClick = false;

	sprite_.Initialize(SpriteCommon::GetInstance(), SpriteLoader::GetInstance()->GetTextureIndex(spriteName + ".png"));
	sprite_.SetAnchorPoint({ 0.5f,0.5f });
	sprite_.SetPozition(position);
	sprite_.Update();
}

void Button::SetSize(Vector2 newSize) {
	sprite_.SetSize(newSize);
	sprite_.Update();
}

void Button::SetPosition(Vector2 newPosition) {
	sprite_.SetPozition(newPosition);
	sprite_.Update();
}

void Button::Update() {
	sprite_.Update();

	Input *input = Input::GetInstance();
	Vector2 mousePos = input->MousePos();
	Vector2 spritePos = sprite_.GetPosition();
	Vector2 spriteSize = sprite_.GetSize();
	Vector2 spriteAnchorPoint = sprite_.GetAnchorPoint();

	float left = (0.0f - spriteAnchorPoint.x) * spriteSize.x + spritePos.x;
	float right = (1.0f - spriteAnchorPoint.x) * spriteSize.x + spritePos.x;
	float top = (0.0f - spriteAnchorPoint.y) * spriteSize.y + spritePos.y;
	float bottom = (1.0f - spriteAnchorPoint.y) * spriteSize.y + spritePos.y;

	if (left <= mousePos.x && right >= mousePos.x && top <= mousePos.y && bottom >= mousePos.y) {	
		isMouseOver = true;
	}else {
		isMouseOver = false;
	}

	isMouseClick = false;
	if (isMouseOver == true) {
		if (input->TriggerMouse(0) == true) {
			isMouseClick = true;
		}
	}
}

void Button::Draw() {
	sprite_.Draw();
}