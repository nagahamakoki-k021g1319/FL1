#pragma once
#include"Sprite.h"
#include<memory>

using namespace MyEngine;

namespace MyEngine {
	class Button {
	public:
		void Initialize(std::string spriteName, Vector2 position = { 0.0f,0.0f });
		void SetSize(Vector2 newSize);
		void SetPosition(Vector2 newPosition);

		void Update();
		void Draw();

		bool IsMouseOver() { return isMouseOver; };
		bool IsMouseClick() { return isMouseClick; };
	private:
		Sprite sprite_;
		bool isMouseOver;
		bool isMouseClick;

	};
}