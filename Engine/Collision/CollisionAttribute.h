/**
 * @file CollisionAttribute.h
 * @brief 当たり判定の属性
 */

#pragma once
//属性
namespace MyEngine {
	enum class Attribute {
		PlyerBody,
		PlayerAttack,
		EnemyBody,
		EnemyAttack,
		EnemyBullet,
		Coin,
		Goal,
		NormalObstacle,
	};

	//何に当たっているか
	struct HitTarget {
		bool playerBody = false;
		bool playerAttack = false;
		bool enemyBody = false;
		bool enemyAttack = false;
		bool enemyBullet = false;
		bool coin = false;
		bool goal = false;
		bool normalObstacle = false;
	};

	//どこで当たっているか
	struct HitPos {
		Vector3 playerBody = { 0,0,0 };
		Vector3 playerAttack = { 0,0,0 };
		Vector3 enemyBody = { 0,0,0 };
		Vector3 enemyAttack = { 0,0,0 };
		Vector3 enemyBullet = { 0,0,0 };
		Vector3 coin = { 0,0,0 };
		Vector3 goal = { 0,0,0 };
		Vector3 normalObstacle = { 0,0,0 };
	};
}