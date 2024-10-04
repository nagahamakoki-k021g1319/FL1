/**
 * @file CollisionManager.h
 * @brief 当たり判定のチェック
 */
#pragma once
#include<forward_list>
#include"CollisionPrimitive.h"

#ifdef _DEBUG
#include"Model.h"
#include"Object3d.h"
#endif

using namespace MyEngine;

class CollisionManager {
public:
	enum ColStack {
		MAXCOL = 600
	};

	~CollisionManager();
	/**
	 * @brief 初期化
	*/
	void Initialize();
	/**
	 * @brief デストラクタ
	*/
	void Finalize();
	/**
	 * @brief 全体の衝突チェック
	*/
	void CheakAllCol();
	/**
	 * @brief インスタンス取得
	*/
	static CollisionManager* GetInstance();
	/**
	 * @brief 当たり判定登録
	*/
	void AddCollider(BaseCollider* collide);
	/**
	 * @brief 当たり判定解除
	*/
	void RemoveCollider(BaseCollider* collide);
	/**
	 * @brief プレイヤー攻撃判定
	*/
	void GetPlayerAttack(const bool playerIsAttack);
	/**
	 * @brief 敵攻撃判定
	*/
	void GetEnemyAttack(const bool enemyIsAttack);
private:
	/**
	 * @brief 個々の衝突判定
	*/
	bool CheakCol(BaseCollider* colA, BaseCollider* colB, Attribute wishBttributeX, Attribute wishAttributeY, bool& isHit);

private:
	bool isPlayerHit_;
	bool isEnemyHit_;
	std::forward_list<BaseCollider*> colliders_;

#ifdef _DEBUG
public:
	/**
	 * @brief 当たり判定可視化
	*/
	void DrawCollider();
private:
	std::unique_ptr<Object3d> objects_[MAXCOL];
#endif
};