/**
 * @file Vector4.h
 * @brief 4次元ベクトル
 */

#pragma once

//4次元ベクトル
namespace MyEngine {
	class Vector4
	{
	public:
		float x;//x成分
		float y;//y成分
		float z;//z成分
		float w;//w

	public:
		Vector4();
		Vector4(float x, float y, float z, float w);

		/**
		 * @brief ノルムを求める
		*/
		float Length()const;
		/**
		 * @brief 長さの二条計算
		*/
		float LengthSquared()const;
		/**
		 * @brief 正規化
		*/
		Vector4 Normalization()const;
		/**
		 * @brief 正規化
		*/
		Vector4& Normal();
		/**
		 * @brief 内積計算
		*/
		float Dot(const Vector4& v)const;
		/**
		 * @brief 外積計算
		 */
		Vector4 Cross(const Vector4& v)const;

		//単項演算子オーバーロード
		Vector4 operator+() const;
		Vector4 operator-() const;

		// 代入演算子オーバーロード
		Vector4& operator+=(const Vector4& v);
		Vector4& operator-=(const Vector4& v);
		Vector4& operator*=(float s);
		Vector4& operator/=(float s);
	};


	//2項演算子オーバーロード
	//※いろんな引数のパターンに対応(引数の順序)するため、以下のように準備してい
	const Vector4 operator+(const Vector4& v1, const Vector4& v2);

	const Vector4 operator-(const Vector4& v1, const Vector4& v2);
	const Vector4 operator*(const Vector4& v, float s);
	const Vector4 operator*(float s, const Vector4& v);
	const Vector4 operator/(const Vector4& v, float s);

	/**
	 * @brief ラープ関数
	*/
	void Vector4Lerp(const Vector4& src1, const Vector4& src2, float t, Vector4& dest);

	/**
	 * @brief ラープ関数
	*/
	Vector4 Vector4Lerp(const Vector4& src1, const Vector4& src2, float t);
}