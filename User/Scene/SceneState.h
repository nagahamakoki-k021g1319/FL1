/**
 * @file SceneState.h
 * @brief シーンのステートパターン基底
 */
#pragma once
#include "Input.h"

class SceneManager;

class SceneState {
public:
	SceneState();
	virtual ~SceneState() = default;
	/**
	 * @brief 初期化
	*/
	virtual void Initialize() = 0;
	/**
	 * @brief 更新
	*/
	virtual void Update() = 0;
	/**
	 * @brief obj描画
	*/
	virtual void ObjectDraw() = 0;
	/**
	 * @brief fbx描画
	*/
	virtual void FbxDraw() = 0;
	/**
	 * @brief スプライト描画
	*/
	virtual void SpriteDraw() = 0;
	/**
	 * @brief シーンマネージャセット
	*/
	static void SetSceneManager(SceneManager* sceneManager) { sceneManager_ = sceneManager; };
protected:
	/**
	 * @brief シーン移行
	*/
	virtual void StateTransition() = 0;
protected:
	static SceneManager* sceneManager_;
};