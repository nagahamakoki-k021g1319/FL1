/**
 * WinApp.h
 * WindowsAPI
 */

#pragma once
#include <Windows.h>
namespace MyEngine {
	class WinApp
	{
	public:
		static LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		/**
		 * @brief Hwnd取得
		*/
		HWND GetHwnd() const { return hwnd_; }

		/**
		 * @brief HInstance取得
		*/
		HINSTANCE GetHInstance() const { return w_.hInstance; }

		/**
		 * @brief メッセージ処理
		*/
		bool ProcessMessage();

		// ウィンドウ横幅
		static const int window_width = 1280;
		// ウィンドウ縦幅
		static const int window_height = 720;

	public: //メンバ関数
		/**
		 * @brief 初期化
		*/
		void Initialize();

		/**
		 * @brief 更新
		*/
		void Update();

		/**
		 * @brief 終了
		*/
		void Finalize();
	private:
		//ウィンドウハンドル
		HWND hwnd_ = nullptr;

		//ウィンドウクラスの設定
		WNDCLASSEX w_{};

	};
}