#include "GameManager.h"
#include <iostream>
#include <string>

GameManager::~GameManager()
{
	if (instance != nullptr)
	{
		delete instance;
	}
}

GameManager* GameManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
	}

	return instance;
}

void GameManager::Init()
{
	std::random_device rd;
	engine.seed(rd());
}

void GameManager::CreatePlayer()
{
	std::string name;
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
			exit(0);
			break;
		default:
			break;
		}
	}
	
}

void GameManager::Battle()
{
	monsters.push_back(SpawnRandomMonsters());

	while ( player->GetHP( ) <= 0 || monsters.isEmpty( ) )
	{

	}
}

Monster* GameManager::SpawnRandomMonsters()
{
	// 몬스터 랜덤 선택
	std::discrete_distribution<int> weightDist({ 40, 30, 20, 10 });		// 꼭 합이 100일 필요는 없음
	int roll = weightDist(engine);

	Monster* newMonster = nullptr;

	switch ( roll )
	{
	case 0:			// 슬라임
		newMonster = new Slime(player->GetPlayerLv()); // 플레이어 레벨 불러오는 함수 확인 필요
		break;
	case 1:			// 고블린
		newMonster = new Goblin(player->GetPlayerLv( ));
		break;
	case 2:			// 오크
		newMonster = new Orc(player->GetPlayerLv( ));
		break;
	case 3:			// 트롤
		newMonster = new Troll(player->GetPlayerLv( ));
		break;
	}

	return newMonster;
}

