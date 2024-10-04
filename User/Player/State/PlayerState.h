/**
 * @file PlayerState.h
 * @brief プレイヤーのステートパターン基底
 */
#pragma once
#include"Vector3.h"
#include"GlobalVariables.h"

using namespace MyEngine;

namespace Player {
	class Main;
	class State {
	public:
		State();
		virtual ~State() {};
		/**
		 * @brief 初期化
		*/
		virtual void Initialize() = 0;
		/**
		 * @brief 更新
		*/
		virtual void Update(Main* player) = 0;

		/**
		 * @brief 移動ベクトル取得
		*/
		Vector3 GetMoveVector() { return moveVector_; };
		/**
		 * @brief 回転ベクトル取得
		*/
		Vector3 GetRotaVector() { return rotaVector_; };
	protected:
		/**
		 * @brief 状態移行
		*/
		virtual void StateTransition(Main* player) = 0;
		/**
		 * @brief 調整項目の適用
		*/
		virtual void ApplyGlobalVariables() = 0;
	protected:
		Vector3 moveVector_;
		Vector3 rotaVector_;
	};
}