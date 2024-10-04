#include "GameManager.h"

void GameManager::Init() { isFlags_["Start"] = false; }

bool GameManager::GetFlags(std::string& name) { return isFlags_[name]; }

void GameManager::SetFlags(std::string& name, bool& isFlag) { isFlags_[name] = isFlag; }
