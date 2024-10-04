/**
 * @file SceneState.h
 * @brief シーン遷移演出
 */
#pragma once
#include<memory>
#include"Sprite.h"

class SceneChange {
public:
	SceneChange();
	/**
	 * @brief 初期化
	*/
	void Initialize();
	/**
	 * @brief 更新
	*/
	void Update();
	/**
	 * @brief スプライト描画
	*/
	void SpriteDraw();
	/**
	 * @brief 暗転開始
	*/
	void FadeOutStart();
	/**
	 * @brief 明転開始
	*/
	void FadeInStart();
	/**
	 * @brief 暗転完了フラグ取得
	*/
	bool GetIsFadeOutFin();

private:
	/**
	 * @brief 明転
	*/
	void FadeIn();
	/**
	 * @brief 暗転
	*/
	void FadeOut();

private:
	std::unique_ptr<Sprite> black_;
	std::unique_ptr<Sprite> loading_;
	//暗転
	bool isFadeOut;
	bool isFadeOutFin;
	float blackAddAlpha;
	//明転
	bool isFadeIn;
	float blackSubtractAlpha;
};