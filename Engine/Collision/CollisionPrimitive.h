/**
 * @file CollisionPrimitive.h
 * @brief 当たり判定の形状
 */

#pragma once
#include"Vector3.h"
#include<DirectXMath.h>
#include"CollisionAttribute.h"

namespace MyEngine {
	class BaseCollider {
	public:
		/**
		 * @brief 中心座標設定
		*/
		void SetCenter(Vector3 center) { center_ = center; };
		/**
		 * @brief 半径設定
		*/
		void SetRad(float rad) { radius_ = rad; };
		/**
		 * @brief 属性設定
		*/
		void SetAttribute(Attribute attribute) { attribute_ = attribute; };

		/**
		 * @brief 攻撃力設定
		*/
		void SetPower(int power) { power_ = power; };
		/**
		 * @brief 攻撃力取得
		*/
		int GetPower() { return power_; };
		/**
		 * @brief ダメージ設定
		*/
		void SetDamage(int damage) { damage_ = damage; };
		/**
		 * @brief ダメージ取得
		*/
		int GetDamage() { return damage_; };

		/**
		 * @brief 衝突判定付与
		*/
		void IsHit(Attribute attribute, Vector3 hitPos);

		/**
		 * @brief 衝突判定解除
		*/
		void RemoveHit(Attribute attribute);

		/**
		 * @brief 中心座標取得
		*/
		Vector3 GetCenter() { return center_; };
		/**
		 * @brief 半径取得
		*/
		float GetRad() { return radius_; };
		/**
		 * @brief 属性取得
		*/
		Attribute GetAttribute() { return attribute_; };
		/**
		 * @brief 衝突判定取得
		*/
		HitTarget GetIsHit() { return isHit_; };
		/**
		 * @brief 衝突位置取得
		*/
		HitPos GetHitPos() { return hitPos_; };

	protected:
		Vector3 center_ = { 0,0,0 };
		float radius_ = 1.0f;
		Attribute attribute_;
		HitTarget isHit_;
		HitPos hitPos_;
		int power_ = 0;
		int damage_ = 0;
	};

	struct Sphere {
		Vector3 center = { 0,0,0 };
		float radius = 1.0f;

		Attribute attribute;
		HitTarget isHit;
	};

	struct Cylinder {
		Vector3 center = { 0,0,0 };
		float radius = 1.0f;
		float height = 1.0f;
	};

	struct Plane {
		Vector3 normal = { 0,1,0 };

		float distance = 0.0f;

	};

	class Triangle {
	public:
		Vector3 p0;
		Vector3 p1;
		Vector3 p2;

		Vector3 normal;

		/**
		 * @brief 正規化
		*/
		void ComputeNormal();
	};

	struct Ray
	{
		Vector3 start = { 0,0,0 };

		Vector3 dir = { 1,0,0 };

	};

	class CollisionPrimitive
	{

	};
}