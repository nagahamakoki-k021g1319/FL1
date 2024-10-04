#pragma once
#include"BaseFieldObject.h"
#include"LevelLoader.h"
#include"Model.h"
#include<memory>
#include<string>
#include<map>
class FieldManager
{
public:
	void Initialize();

	void Load(const std::string& num);
private:
	std::unique_ptr<LevelData> jsonLoader_;
	std::map<std::string, std::unique_ptr<Model>> models;
};

