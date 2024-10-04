/**
 * @file GameMain.h
 * @brief ゲーム全体の流れ
 */
#pragma once
#include"Framework .h"
#include"SceneManager.h"

using namespace std;

class GameMain : public Framework {
public:
	GameMain();
	~GameMain();
	/**
	 * @brief 初期化
	*/
	virtual void Initialize();
private:
	/**
	 * @brief 破棄
	*/
	void Finalize() override;
	/**
	 * @brief 更新
	*/
	void Update() override;
	/**
	 * @brief 描画
	*/
	void Draw() override;
	/**
	 * @brief 終了フラグ
	*/
	bool IsEndRequst() override;
private:
	SceneManager* sceneManager_ = nullptr;
};