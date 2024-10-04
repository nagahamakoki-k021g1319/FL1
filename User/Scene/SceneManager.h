/**
 * @file SceneManager.h
 * @brief シーン管理
 */
#pragma once
#include "DirectXCommon.h"
#include "SceneState.h"
#include "SceneChange.h"

class SceneManager {
public:
	enum class SCENE {
		TITLE,
		SELECT,
		GAME,
	};

public:
	SceneManager();
	~SceneManager();
	/**
	 * @brief 初期化
	*/
	void Initialize(DirectXCommon* dxCommon);
	/**
	 * @brief シーン移行
	*/
	void TransitionTo(SCENE nextScene);
	/**
	 * @brief 更新
	*/
	void Update();
	/**
	 * @brief 描画
	*/
	void Draw();

private:
	void ChangeScene();

private:
	DirectXCommon* dxCommon_ = nullptr;

private:
	std::unique_ptr<SceneState> state_ = nullptr;
	SCENE nextScene_;
	std::unique_ptr<SceneChange> sceneChange_ = nullptr;
};