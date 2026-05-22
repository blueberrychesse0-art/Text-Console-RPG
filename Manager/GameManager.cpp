#include "GameManager.h"
#include <iostream>

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

void GameManager::CreatePlayer()
{
	string name;
	std::cout << "플레이어 이름을 입력해 주세요: ";
	std::cin >> name;

	player = new Character(name);
}

void GameManager::Main()
{
	int select = -1;

	while (1)
	{
		std::cout << "======== Text-Console RPG ========" << std::endl;
		std::cout << "1. 던전 입장" << std::endl;
		std::cout << "0. 게임 종료" << std::endl;
		std::cout << "==================================" << std::endl;
		std::cout << "선택 : ";
		std::cin >> select;

		switch (select)
		{
		case 1:
			Battle();
			break;
		case 2:
			break;
		case 0:
			system.eixt(0);
			break;
		default:
			break;
		}
	}
	
}

void GameManager::Battle()
{

}


