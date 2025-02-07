#pragma once
#include"Sprite.h"
#include<memory>

using namespace MyEngine;

namespace MyEngine {
	class Button {
	public:
		void Initilize();
		void Update();
		void Draw();

		bool isMouseOver();
		bool isMouseclick();

	private:
		std::unique_ptr<Sprite> sprite_;
		Vector2 spritePos_;
		Vector2 spriteSize_;

	};
}