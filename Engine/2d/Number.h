#pragma once
#include<cstdint>

#include"Sprite.h"
#include"SpriteLoader.h"

#include<Vector2.h>

using namespace MyEngine;

class Number
{
private:
	Sprite						sprite_[5];
	Vector2						drawSize_;
public:

	Number();
	~Number();

	void Initialize();

	void Draw(const Vector2& pos, size_t num, float scl = 1.0f);
};

