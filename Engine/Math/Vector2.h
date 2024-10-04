/**
 * @file Vector2.h
 * @brief 2次元ベクトル
 */
#pragma once
namespace MyEngine {
	class Vector2
	{
	public:
		float x;	//x成分
		float y;	//y成分

	public:
		Vector2();					//零ベクトルとして生成
		Vector2(float x, float y);	//x成分、ｙ成分を指定しての生成

		/**
		 * @brief ノルム計算
		*/
		float length() const;
		/**
		 * @brief 正規化
		*/
		Vector2& nomalize();
		/**
		 * @brief 内積計算
		*/
		float dot(const Vector2& v) const;
		/**
		 * @brief 外積計算
		*/
		float cross(const Vector2& v) const;

		//単項演算子オーバーロード
		Vector2 operator+() const;
		Vector2 operator-() const;

		//代入演算子オーバーロード
		Vector2& operator+=(const Vector2& v);
		Vector2& operator-=(const Vector2& v);
		Vector2& operator*=(float s);
		Vector2& operator/=(float s);
	};

	//二項演算子オーバーロード
	//※いろんな引数（引数の方と順序）のパターンに対応するため、以下のように準備している
	const Vector2 operator+(const Vector2& v1, const Vector2& v2);
	const Vector2 operator-(const Vector2& v1, const Vector2& v2);
	const Vector2 operator*(const Vector2& v, float s);
	const Vector2 operator*(float s, const Vector2& v);
	const Vector2 operator/(const Vector2& v, float s);
}