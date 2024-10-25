/**
 * @file Easing.h
 * @brief イージング関数
 */

#include "Easing.h"
using namespace MyEngine;

float Easing::lerpFloat(const float start, const float end, const float t) {
	return start * (1.0f - t) + end * t;
}

// Quad
float Easing::InQuadFloat(const float start, const float end, const float time)
{
	float t = powf(time, 2.0f);

	return start * (1.0f - t) + end * t;
}

float Easing::OutQuadFloat(const float start, const float end, const float time)
{
	float t = (1.0f - powf(1.0f - time, 2.0f));

	return start * (1.0f - t) + end * t;
}

float Easing::InOutQuadFloat(const float start, const float end, const float time)
{
	float t;
	if (time < 0.5f)
	{
		t = 2.0f * powf(time, 2.0f);
	}
	else
	{
		t = (1.0f - powf(-2.0f * time + 2.0f, 2.0f) / 2.0f);
	}

	return start * (1.0f - t) + end * t;
}

Vector2 Easing::InQuadVec2(const Vector2& start, const Vector2& end, const float time)
{
	float t = powf(time, 2.0f);
	Vector2 A, B;
	A = Vector2(start.x * (1.0f - t), start.y * (1.0f - t));
	B = Vector2(end.x * t, end.y * t);

	Vector2 position;
	position = Vector2(A.x + B.x, A.y + B.y);
	return position;
}

Vector2 Easing::OutQuadVec2(const Vector2& start, const Vector2& end, const float time)
{
	float t = (1.0f - powf(1.0f - time, 2.0f));
	Vector2 A, B;
	A = Vector2(start.x * (1.0f - t), start.y * (1.0f - t));
	B = Vector2(end.x * t, end.y * t);

	Vector2 position;
	position = Vector2(A.x + B.x, A.y + B.y);
	return position;
}

Vector2 Easing::InOutQuadVec2(const Vector2& start, const Vector2& end, const float time)
{
	float t;
	if (time < 0.5f)
	{
		t = 2.0f * powf(time, 2.0f);
	}
	else
	{
		t = (1.0f - powf(-2.0f * time + 2.0f, 2.0f) / 2.0f);
	}

	Vector2 A, B;
	A = Vector2(start.x * (1.0f - t), start.y * (1.0f - t));
	B = Vector2(end.x * t, end.y * t);

	Vector2 position;
	position = Vector2(A.x + B.x, A.y + B.y);
	return position;
}

Vector3 Easing::InQuadVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t = powf(time, 2.0f);
	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}

Vector3 Easing::OutQuadVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t = (1.0f - powf(1.0f - time, 2.0f));
	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}

Vector3 Easing::InOutQuadVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t;
	if (time < 0.5f)
	{
		t = 2.0f * powf(time, 2.0f);
	}
	else
	{
		t = (1.0f - powf(-2.0f * time + 2.0f, 2.0f) / 2.0f);
	}

	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}

// Cubic
float Easing::InCubicFloat(const float start, const float end, const float time)
{
	float t = powf(time, 3.0f);

	return start * (1.0f - t) + end * t;
}

float Easing::OutCubicFloat(const float start, const float end, const float time)
{
	float t = (1.0f - powf(1.0f - time, 3.0f));

	return start * (1.0f - t) + end * t;
}

float Easing::InOutCubicFloat(const float start, const float end, const float time)
{
	float t;
	if (time < 0.5f)
	{
		t = 4.0f * powf(time, 3.0f);
	}
	else
	{
		t = (1.0f - powf(-2.0f * time + 2.0f, 3.0f) / 2.0f);
	}

	return start * (1.0f - t) + end * t;
}

Vector2 Easing::InCubicVec2(const Vector2& start, const Vector2& end, const float time)
{
	float t = powf(time, 3.0f);
	Vector2 A, B;
	A = Vector2(start.x * (1.0f - t), start.y * (1.0f - t));
	B = Vector2(end.x * t, end.y * t);

	Vector2 position;
	position = Vector2(A.x + B.x, A.y + B.y);
	return position;
}

Vector2 Easing::OutCubicVec2(const Vector2& start, const Vector2& end, const float time)
{
	float t = (1.0f - powf(1.0f - time, 3.0f));
	Vector2 A, B;
	A = Vector2(start.x * (1.0f - t), start.y * (1.0f - t));
	B = Vector2(end.x * t, end.y * t);

	Vector2 position;
	position = Vector2(A.x + B.x, A.y + B.y);
	return position;
}

Vector2 Easing::InOutCubicVec2(const Vector2& start, const Vector2& end, const float time)
{
	float t;
	if (time < 0.5f)
	{
		t = 4.0f * powf(time, 3.0f);
	}
	else
	{
		t = (1.0f - powf(-2.0f * time + 2.0f, 3.0f) / 2.0f);
	}

	Vector2 A, B;
	A = Vector2(start.x * (1.0f - t), start.y * (1.0f - t));
	B = Vector2(end.x * t, end.y * t);

	Vector2 position;
	position = Vector2(A.x + B.x, A.y + B.y);
	return position;
}

Vector3 Easing::InCubicVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t = powf(time, 3.0f);
	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}

Vector3 Easing::OutCubicVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t = (1.0f - powf(1.0f - time, 3.0f));
	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}

Vector3 Easing::InOutCubicVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t;
	if (time < 0.5f)
	{
		t = 4.0f * powf(time, 3.0f);
	}
	else
	{
		t = (1.0f - powf(-2.0f * time + 2.0f, 3.0f) / 2.0f);
	}

	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}

// Quart
float Easing::InQuartFloat(const float start, const float end, const float time)
{
	float t = powf(time, 4.0f);

	return start * (1.0f - t) + end * t;
}

float Easing::OutQuartFloat(const float start, const float end, const float time)
{
	float t = (1.0f - powf(1.0f - time, 4.0f));

	return start * (1.0f - t) + end * t;
}

float Easing::InOutQuartFloat(const float start, const float end, const float time)
{
	float t;
	if (time < 0.5f)
	{
		t = 8.0f * powf(time, 4.0f);
	}
	else
	{
		t = (1.0f - powf(-2.0f * time + 2.0f, 4.0f) / 2.0f);
	}

	return start * (1.0f - t) + end * t;
}

Vector2 Easing::InQuartVec2(const Vector2& start, const Vector2& end, const float time)
{
	float t = powf(time, 4.0f);
	Vector2 A, B;
	A = Vector2(start.x * (1.0f - t), start.y * (1.0f - t));
	B = Vector2(end.x * t, end.y * t);

	Vector2 position;
	position = Vector2(A.x + B.x, A.y + B.y);
	return position;
}

Vector2 Easing::OutQuartVec2(const Vector2& start, const Vector2& end, const float time)
{
	float t = (1.0f - powf(1.0f - time, 4.0f));
	Vector2 A, B;
	A = Vector2(start.x * (1.0f - t), start.y * (1.0f - t));
	B = Vector2(end.x * t, end.y * t);

	Vector2 position;
	position = Vector2(A.x + B.x, A.y + B.y);
	return position;
}

Vector2 Easing::InOutQuartVec2(const Vector2& start, const Vector2& end, const float time)
{
	float t;
	if (time < 0.5f)
	{
		t = 8.0f * powf(time, 4.0f);
	}
	else
	{
		t = (1.0f - powf(-2.0f * time + 2.0f, 4.0f) / 2.0f);
	}

	Vector2 A, B;
	A = Vector2(start.x * (1.0f - t), start.y * (1.0f - t));
	B = Vector2(end.x * t, end.y * t);

	Vector2 position;
	position = Vector2(A.x + B.x, A.y + B.y);
	return position;
}

Vector3 Easing::InQuartVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t = powf(time, 4.0f);
	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}

Vector3 Easing::OutQuartVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t = (1.0f - powf(1.0f - time, 4.0f));
	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}

Vector3 Easing::InOutQuartVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t;
	if (time < 0.5f)
	{
		t = 8.0f * powf(time, 4.0f);
	}
	else
	{
		t = (1.0f - powf(-2.0f * time + 2.0f, 4.0f) / 2.0f);
	}

	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}

// Quint
float Easing::InQuintFloat(const float start, const float end, const float time)
{
	float t = powf(time, 5.0f);

	return start * (1.0f - t) + end * t;
}

float Easing::OutQuintFloat(const float start, const float end, const float time)
{
	float t = (1.0f - powf(1.0f - time, 4.0f));

	return start * (1.0f - t) + end * t;
}

float Easing::InOutQuintFloat(const float start, const float end, const float time)
{
	float t;
	if (time < 0.5f)
	{
		t = 16.0f * powf(time, 5.0f);
	}
	else
	{
		t = (1.0f - powf(-2.0f * time + 2.0f, 5.0f) / 2.0f);
	}

	return start * (1.0f - t) + end * t;
}

Vector2 Easing::InQuintVec2(const Vector2& start, const Vector2& end, const float time)
{
	float t = powf(time, 5.0f);
	Vector2 A, B;
	A = Vector2(start.x * (1.0f - t), start.y * (1.0f - t));
	B = Vector2(end.x * t, end.y * t);

	Vector2 position;
	position = Vector2(A.x + B.x, A.y + B.y);
	return position;
}

Vector2 Easing::OutQuintVec2(const Vector2& start, const Vector2& end, const float time)
{
	float t = (1.0f - powf(1 - time, 5.0f));
	Vector2 A, B;
	A = Vector2(start.x * (1.0f - t), start.y * (1.0f - t));
	B = Vector2(end.x * t, end.y * t);

	Vector2 position;
	position = Vector2(A.x + B.x, A.y + B.y);
	return position;
}

Vector2 Easing::InOutQuintVec2(const Vector2& start, const Vector2& end, const float time)
{
	float t;
	if (time < 0.5f)
	{
		t = 16.0f * powf(time, 5.0f);
	}
	else
	{
		t = (1.0f - powf(-2.0f * time + 2.0f, 5.0f) / 2.0f);
	}

	Vector2 A, B;
	A = Vector2(start.x * (1.0f - t), start.y * (1.0f - t));
	B = Vector2(end.x * t, end.y * t);

	Vector2 position;
	position = Vector2(A.x + B.x, A.y + B.y);
	return position;
}

Vector3 Easing::InQuintVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t = powf(time, 5.0f);
	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}

Vector3 Easing::OutQuintVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t = (1.0f - powf(1.0f - time, 5.0f));
	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}

Vector3 Easing::InOutQuintVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t;
	if (time < 0.5f)
	{
		t = 16.0f * powf(time, 5.0f);
	}
	else
	{
		t = (1.0f - powf(-2.0f * time + 2.0f, 5.0f) / 2.0f);
	}

	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}