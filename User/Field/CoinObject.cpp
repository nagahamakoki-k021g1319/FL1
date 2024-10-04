#include "CoinObject.h"
#include"CountCoin.h"

CoinObject::CoinObject(Model* Model, Vector3 Pos, Vector3 Scale)
{
	object = Object3d::Create();
	object->SetModel(Model);

	object->wtf.position = Pos;
	object->wtf.scale = Scale;

	sphere = new BaseCollider;

	//半径セット
	sphere->SetRad(1.0f);
	//中心座標
	sphere->SetCenter(Pos);
	//属性付与*1
	sphere->SetAttribute(Attribute::Coin);
	//当たり判定をマネージャにセット
	CollisionManager::GetInstance()->AddCollider(sphere);
	//影
	
}

void CoinObject::Update()
{

	object->wtf.rotation.y += 0.5f;

	if (sphere->GetIsHit().playerBody){
		isDelete = true;
		CountCoin::num_++;
	}

	object->Update();
	
}

void CoinObject::Draw()
{
	object->Draw();
}
