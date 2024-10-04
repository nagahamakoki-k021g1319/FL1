/**
 * @file SpriteLoader.h
 * @brief スプライト読み込み
 */

#pragma once
#include"Sprite.h"
#include<map>
#include<string>

class SpriteLoader {
public:
	/**
	 * @brief インスタンス取得
	*/
	static SpriteLoader* GetInstance();

	/**
	 * @brief ファイル内全読み込み
	*/
	void LoadAllTexture();

	/**
	 * @brief 指定名の画像読み込み
	*/
	void LoadTexture(const std::string& spriteName);

	/**
	 * @brief インスタンス取得
	*/
	uint32_t GetTextureIndex(const std::string& spriteName);

private:
	//ファイルパス
	const std::string kDirectoryPath = "Resources/Sprite/";
	std::map<std::string, uint32_t> items_;
	uint32_t textureIndex_ = 0;
};