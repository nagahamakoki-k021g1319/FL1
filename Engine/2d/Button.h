#pragma once
#include"Sprite.h"
#include<memory>

using namespace MyEngine;

namespace MyEngine {
	class Button {
	public:
		void Initilize(std::string spriteName, Vector2 position);
		void Update();
		void Draw();

		bool IsMouseOver() { return isMouseOver; };
		bool IsMouseClick() { return isMouseClick; };

	private:
		std::unique_ptr<Sprite> sprite_;
		bool isMouseOver;
		bool isMouseClick;

	};
}