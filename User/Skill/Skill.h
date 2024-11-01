#pragma once
#include<map>
#include<string>

#include"Sprite.h"
#include"SpriteLoader.h"

class Skills {
public:
	struct Skill{
		std::string name_;
		int cost_;
		int score_;
		int shield_;
		Sprite sprite_;
	};

public:
	void Initilize();
	void AddSkill(std::string name, int score, int cost, int shield);
	
	Skill GetSkill(std::string name);
private:
	std::map<std::string, Skill> skills_;

};