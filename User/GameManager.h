#pragma once
#include <map>
#include <string>

class GameManager {
public:
	void Init();

	bool GetFlags(std::string& name);

	void SetFlags(std::string& name,bool& isFlag);

private:
	std::map<std::string, bool> isFlags_;
};
