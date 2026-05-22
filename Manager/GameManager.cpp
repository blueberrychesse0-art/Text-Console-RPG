#include "GameManager.h"

GameManager::~GameManager()
{
	if (instance != nullptr)
	{
		delete instance;
	}
}

GameManager* GameManager::getInstance()
{
	if (instance != nullptr)
	{
		instance = new GameManager();
	}

	return instance;
}

void GameManager::Init()
{

}

void GameManager::Main()
{

}

void GameManager::CreatePlayer()
{
	// 
}
