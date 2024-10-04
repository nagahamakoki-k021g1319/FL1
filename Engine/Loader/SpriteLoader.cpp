/**
 * @file SpriteLoader.cpp
 * @brief スプライト読み込み
 */
#include"SpriteLoader.h"
#include<fstream>
#include<json.hpp>

SpriteLoader* SpriteLoader::GetInstance() {
	static SpriteLoader instance;
	return &instance;
}

void SpriteLoader::LoadAllTexture() {
	SpriteCommon::GetInstance()->Initialize();
	std::filesystem::path dir(kDirectoryPath);

	//ディレクトリ内各ファイル処理
	std::filesystem::directory_iterator dir_it(dir);
	for (const std::filesystem::directory_entry& entry : dir_it) {
		//ファイルパス取得
		const std::filesystem::path& filePath = entry.path();
		//ファイル拡張子取得
		std::string extension = filePath.extension().string();
		//pngファイル以外スキップ
		if (extension.compare(".png") != 0) {
			continue;
		}
		//ファイル読み込み
		LoadTexture(filePath.stem().string());
	}
}

void SpriteLoader::LoadTexture(const std::string& spriteName) {
	std::string filePath = spriteName + ".png";
	SpriteCommon::GetInstance()->LoadTexture(textureIndex_, filePath);
	items_[filePath] = textureIndex_;
	textureIndex_++;
}

uint32_t SpriteLoader::GetTextureIndex(const std::string& spriteName) {
	return items_.at(spriteName);
}