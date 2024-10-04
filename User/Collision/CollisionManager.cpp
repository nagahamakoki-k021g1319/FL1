/**
 * @file CollisionManager.cpp
 * @brief 当たり判定のチェック
 */
#ifdef _DEBUG
#include"ObjLoader.h"
#endif

#include"CollisionManager.h"
#include"Collision.h"

void CollisionManager::Initialize() {
	isPlayerHit_ = false;
	isEnemyHit_ = false;

#ifdef _DEBUG
	Model* model_ = ObjLoader::GetInstance()->GetModel("collider");
	for (int i = 0; i < MAXCOL; i++) {
		objects_[i] = Object3d::Create();
		objects_[i]->SetModel(model_);
	}
#endif
}

CollisionManager::~CollisionManager() {}

CollisionManager* CollisionManager::GetInstance(){
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::AddCollider(BaseCollider* collide){
	colliders_.push_front(collide);
};

void CollisionManager::RemoveCollider(BaseCollider* collide){
	colliders_.remove(collide);
};

void CollisionManager::Finalize() {
	colliders_.clear();
};

void CollisionManager::CheakAllCol() {
	isEnemyHit_ = false;
	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;
	itA = colliders_.begin();
	for (; itA != colliders_.end(); ++itA) {
		BaseCollider* colA = *itA;
		itB = itA;
		++itB;
		for (; itB != colliders_.end(); ++itB) {
			BaseCollider* colB = *itB;
			//自機と敵突進
			if (CheakCol(colA, colB, Attribute::PlyerBody, Attribute::EnemyAttack, isPlayerHit_)) {}
			//自機と敵弾
			else if(CheakCol(colA, colB, Attribute::PlyerBody, Attribute::EnemyBullet, isPlayerHit_)) {}
			//自機攻撃と敵機
			else if(CheakCol(colA, colB, Attribute::PlayerAttack, Attribute::EnemyBody, isEnemyHit_)) {}
			//金と人
			else if (CheakCol(colA, colB, Attribute::PlyerBody, Attribute::Coin, isEnemyHit_)) {}
			//ゴールと人
			else if (CheakCol(colA, colB, Attribute::PlyerBody, Attribute::Goal, isEnemyHit_)) {}
			//障害と人
			else if (CheakCol(colA, colB, Attribute::PlyerBody, Attribute::NormalObstacle, isEnemyHit_)) {}
		}
	}
}

bool CollisionManager::CheakCol(BaseCollider* colA, BaseCollider* colB, Attribute wishAttributeX, Attribute wishAttributeY, bool& isHit) {
	if (colA->GetAttribute() == wishAttributeX && colB->GetAttribute() == wishAttributeY) {
		Vector3 hitPos;
		if (isHit == false) {
			if (Collision::CheckSphere2Sphere(*colA, *colB, &hitPos)) {
				colA->IsHit(colB->GetAttribute(), hitPos);
				colA->SetDamage(colB->GetPower());
				colB->IsHit(colA->GetAttribute(), hitPos);
				colB->SetDamage(colA->GetPower());
				isHit = true;
			}
		}
		return true;
	}else if (colA->GetAttribute() == wishAttributeY && colB->GetAttribute() == wishAttributeX) {
		Vector3 hitPos;
		if (isHit == false) {
			if (Collision::CheckSphere2Sphere(*colA, *colB, &hitPos)) {
				colA->IsHit(colB->GetAttribute(), hitPos);
				colA->SetDamage(colB->GetPower());
				colB->IsHit(colA->GetAttribute(), hitPos);
				colB->SetDamage(colA->GetPower());
				isHit = true;
			}
		}
		return true;
	}
	return false;
}

void CollisionManager::GetPlayerAttack(bool playerIsAttack) {
	if (playerIsAttack == false) {
		isEnemyHit_ = false;
	}
}

void CollisionManager::GetEnemyAttack(bool enemyIsAttack) {
	if (enemyIsAttack == false) {
		isPlayerHit_ = false;
	}
}

#ifdef _DEBUG
void CollisionManager::DrawCollider() {
	std::forward_list<BaseCollider*>::iterator it;
	it = colliders_.begin();
	int i = 0;

	for (; it != colliders_.end(); ++it) {
		BaseCollider* col = *it;
		objects_[i]->wtf.position = col->GetCenter();
		objects_[i]->wtf.scale = { col->GetRad(),col->GetRad() ,col->GetRad() };
		objects_[i]->Update();
		objects_[i]->Draw();
		i++;
	}
}
#endif