#include "Manager/GameManager.h"

GameManager* GameManager::instance = nullptr;

int main()
{
	GameManager::getInstance()->Init();
	GameManager::getInstance()->Main();

	return 0;
}