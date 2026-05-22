#include "GameManager.h"
//
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
	Battle();
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

	
	while (player->GetHealth() <= 0 || monsters.empty())
	{
		int preHealth = monsters[0]->GetHealth();		// 공격 받기 전 체력

		// 플레이어의 공격
		player->Attack();
		monsters[0]->TakeDamage(player->GetAttack());
		std::cout << monsters[0]->GetName( ) << "에게 " << player->GetAttack( ) << " 데미지!" << std::endl;
		std::cout << monsters[0]->GetName( ) << "체력 " << preHealth << " -> " << monsters[0]->GetHealth() << std::endl;

		if (monsters[0]->GetHealth( ) <= 0)			// 몬스터가 죽었을 시
		{
			std::cout << "전투 승리! " << std::endl;

			static std::random_device rd;					// 랜덤 함수
			static std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dist(10 , 21);		// 10 <= x < 21 

			int money = dist(gen);
			player->AddGold(money);			// 골드 추가
			std::cout << "골드 " << money << " 획득!" << std::endl;

			player->AddExperience(50);		// 경험치 추가

			std::uniform_int_distribution<int> percent(0 , 10);
			if (percent(gen) < 3)				// 아이템 추가
			{
				//TODO: 플레이어 아이템추가 함수
			}

			for (Monster* m : monsters)
			{
				delete m;
			}
			monsters.clear( );
			break;
		}

		// 몬스터의 공격
		preHealth = player->GetHealth( );
		monsters[0]->Attack( );
		player->TakeDamage(monsters[0]->GetAttack( ));
		std::cout << player->GetName( ) << "에게 " << monsters[0]->GetAttack() << " 데미지!" << std::endl;
		std::cout << player->GetName( ) << "체력 " << preHealth << " -> " << player->GetHealth( ) << std::endl;

		if (player->GetHealth( ) <= 0)			// 플레이어가가 죽었을 시
		{
			std::cout << "전투 패배! " << std::endl;
			exit(0); // 일단 임시로 패배시 게임종료
			break;
		}
	}
}

Monster* GameManager::SpawnRandomMonsters()
{
	// 몬스터 랜덤 선택
	std::discrete_distribution<int> weightDist({ 40, 30, 20, 10 });		// 꼭 합이 100일 필요는 없음
	int roll = weightDist(engine);

	Monster* newMonster = nullptr;

	switch (roll)
	{
	case 0:			// 슬라임
		newMonster = new Slime(player->GetLevel());
		break;
	case 1:			// 고블린
		newMonster = new Goblin(player->GetLevel( ));
		break;
	case 2:			// 오크
		newMonster = new Orc(player->GetLevel( ));
		break;
	case 3:			// 트롤
		newMonster = new Troll(player->GetLevel( ));
		break;
	}

	return newMonster;
}

