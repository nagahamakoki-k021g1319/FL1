/**
 * @file PlayerJump.h
 * @brief プレイヤーのジャンプパターン
 */
#pragma once

#include"PlayerState.h"
#include"Transform.h"

namespace Player {
	class Jump : public State {
	public:
		Jump();
		~Jump();
		/**
		 * @brief 初期化
		*/
		virtual void Initialize() override;
		/**
		 * @brief 更新
		*/
		void Update(Main* player) override;
	private:
		/**
		 * @brief 移動
		*/
		void Move(const Transform wtf);
		/**
		 * @brief 回転
		*/
		void Rota();
		/**
		 * @brief 状態移行
		*/
		void StateTransition(Main* player) override;
		/**
		 * @brief 調整項目の適用
		*/
		void ApplyGlobalVariables() override;
	private:
		const char* groupName_ = "playerJump";
		float maxSpeed_;
		float maxHeight_;
		int timer_;
		int reachTime_;
		float rotaSpeed_;
	};
}