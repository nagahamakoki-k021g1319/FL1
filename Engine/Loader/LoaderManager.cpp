/**
 * @file LoaderManager.cpp
 * @brief 様々なものの読み込み管理
 */
#include"LoaderManager.h"
#include"GlobalVariables.h"
#include"ObjLoader.h"
#include"SpriteLoader.h"

void LoaderManager::Load() {
	GlobalVariables::GetInstance()->LoadFiles();
	ObjLoader::GetInstance()->LoadAllModel();
	SpriteLoader::GetInstance()->LoadAllTexture();
}