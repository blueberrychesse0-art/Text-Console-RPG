#include "Manager/GameManager.h"

GameManager* GameManager::instance = nullptr;

int main()
{
	GameManager::getInstance()->Init();
	GameManager::getInstance()->CreatePlayer();
	GameManager::getInstance()->Main();

	return 0;
}