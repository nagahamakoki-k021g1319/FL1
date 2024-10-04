/**
 * @file ObjLoader.h
 * @brief objモデル読み込み
 */
#pragma once
#include"Model.h"
#include<map>
#include<string>

using namespace MyEngine;

class ObjLoader {
public:
	/**
	 * @brief インスタンス取得
	*/
	static ObjLoader* GetInstance();

	/**
	 * @brief ファイル内全読み込み
	*/
	void LoadAllModel();

	/**
	 * @brief 指定名の画像読み込み
	*/
	void LoadModel(const std::string& modelName);

	/**
	 * @brief インスタンス取得
	*/
	Model* GetModel(const std::string& modelName);

private:
	//ファイルパス
	const std::string kDirectoryPath = "Resources/Model/";
	std::map<std::string, std::unique_ptr<Model>> items_;
};