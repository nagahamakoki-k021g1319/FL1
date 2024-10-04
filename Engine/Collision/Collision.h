/**
 * @file Collision.h
 * @brief 衝突判定関数
 */

#pragma once

#include "CollisionPrimitive.h"
#include "Vector3.h"

namespace MyEngine {
	class Collision
	{
	public:
		/**
		 * @brief 点と三角形の最近接点
		*/
		static void ClosestPtPoint2Triangle(const Vector3& point, const Triangle& triangle, Vector3* closest);

		/**
		 * @brief 球と法線付き三角形
		*/
		static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, Vector3* inter = nullptr);

		/**
		 * @brief 球と平面の当たり判定
		*/
		static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, Vector3* inter = nullptr);

		/**
		 * @brief レイと平面の当たり判定
		*/
		static bool CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance = nullptr, Vector3* inter = nullptr);

		/**
		 * @brief レイと法線付き三角形の当たり判定
		*/
		static bool CheckRay2Triangle(const Ray& ray, const Triangle& triangle, float* distance = nullptr, Vector3* inter = nullptr);

		/**
		 * @brief レイと球の当たり判定
		*/
		static bool CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance = nullptr, Vector3* inter = nullptr);

		/**
		 * @brief 球と球の当たり判定
		*/
		static bool CheckSphere2Sphere(BaseCollider& sphere1, BaseCollider& sphere2, Vector3* inter = nullptr);

		/**
		 * @brief 球と円柱の当たり判定
		*/
		static bool CheckSphere2Cylinder(Sphere& sphere, Cylinder& cylinder, Vector3* inter = nullptr);

		/**
		 * @brief 円柱と円柱の当たり判定
		*/
		static bool CheckCylinder2Cylinder(Cylinder& cylinder1, Cylinder& cylinder2);

		/**
		 * @brief 当たり判定
		*/
		bool BoxCollision(Vector3 player, Vector3 enemy, Vector3 playerWidth, Vector3 enemyWidth);

		/**
		 * @brief 四角と円の当たり判定
		*/
		bool BoxCircle(Vector3 boxPos, Vector3 circlePos, Vector3 boxWidth, float circleWidth);

		/**
		 * @brief 円の当たり判定
		*/
		static bool CircleCollision(Vector3 playerPos, Vector3 enemyPos, float playerWidth, float enemyWidth);

		/**
		 * @brief 円の当たり判定
		*/
		static bool CircleCollisionXZ(Vector3 playerPos, Vector3 enemyPos, float playerWidth, float enemyWidth);
	};
}