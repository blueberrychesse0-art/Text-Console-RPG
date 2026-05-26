#include "GameManager.h"

GameManager::~GameManager()
{
	if ( player != nullptr )
	{
		delete player;
		player = nullptr;
	}

	for (Monster* m : monsters)
	{
		if (m != nullptr) delete m;
	}
	monsters.clear();
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
	CreatePlayer();
}

void GameManager::Release()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
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
	// CreatePlayer가 제대로 실행되지않아 player가 없으면 실행하지않음
	if (player == nullptr)
		return;

	int select = -1;

	while (1)
	{
		std::cout << "\n========= Text-Console RPG =========" << std::endl;
		std::cout << "1. 던전 입장" << std::endl;
		std::cout << "0. 게임 종료" << std::endl;

		player->DisplayStatus();

		std::cout << "\n선택 : ";
		std::cin >> select;

		switch (select)
		{
		case 1:
			if ( player->GetLevel() >= 10 )	// 플레이어가 10랩이상이면 보스스폰
			{
				EncounterBoss();
			}
			else
			{
				if ( monsters.empty() )		// 일반 몬스터 스폰
				{
					monsters.push_back(SpawnRandomMonsters(1.0f));
					std::cout << "\n" << monsters[0]->GetName() << "(이)가 나타났다! " << std::endl;
				}
			}
			Battle();
			break;
		case 2:
			break;
		case 0:
			return;
			break;
		default:
			break;
		}
	}
	
}

void GameManager::Battle()
{
	// 몬스터가 없으면 실행하지 않음
	if ( monsters.empty() || monsters[0] == nullptr || player == nullptr) 
		return;

	while (player->GetHealth() > 0 && !monsters.empty())
	{
		// 플레이어의 공격
		player->Attack();
		monsters[0]->TakeDamage(player->GetAttack());

		if (monsters[0]->GetHealth() <= 0)			// 몬스터가 죽었을 시
		{
			std::cout << "\n전투 승리! " << std::endl;

			std::uniform_int_distribution<int> dist(10 , 21);		// 10 <= x < 21 

			int money = dist(engine);
			player->AddGold(money);			// 골드 추가
			std::cout << "골드 " << money << " 획득!" << std::endl;
			
			player->AddExperience(50);		// 경험치 추가

			std::uniform_int_distribution<int> percent(0 , 10);
			if (percent(engine) < 3)				// 아이템 추가
			{
				//TODO: 플레이어 아이템추가 함수
			}

			for (Monster* m : monsters)
			{
				delete m;
			}
			monsters.clear();
			break;
		}

		std::cout << std::endl;
		// 몬스터의 공격
		monsters[0]->Attack();
		player->TakeDamage(monsters[0]->GetAttack());

		if (player->GetHealth() <= 0)			// 플레이어가가 죽었을 시
		{
			std::cout << "전투 패배! " << std::endl;
			exit(0); // 일단 임시로 패배시 게임종료
			break;
		}
	}
}

void GameManager::EncounterBoss()
{
	if (monsters.empty())
	{
		std::uniform_real_distribution<float> dist(1.0f , 1.5f);
		float multiply = dist(engine);

		monsters.push_back(SpawnRandomMonsters(multiply));
		std::cout << "\n[BOSS] 강력한 " << monsters[0]->GetName( ) << " 이 나타났다! " << std::endl;
	}
}

Monster* GameManager::SpawnRandomMonsters(float multiply)
{
	// 몬스터 랜덤 선택
	std::discrete_distribution<int> weightDist({ 40, 30, 20, 10 });		// 꼭 합이 100일 필요는 없음
	int roll = weightDist(engine);

	Monster* newMonster = nullptr;
	int playerLevel = player->GetLevel();

	switch (roll)
	{
	case 0:			// 슬라임
		newMonster = new Slime(playerLevel);
		break;
	case 1:			// 고블린
		newMonster = new Goblin(playerLevel);
		break;
	case 2:			// 오크
		newMonster = new Orc(playerLevel);
		break;
	case 3:			// 트롤
		newMonster = new Troll(playerLevel);
		break;
	default:
		newMonster = new Slime(playerLevel);
		break;
	}

	// 몬스터 스탯 배율 적용
	if (newMonster != nullptr)
	{
		newMonster->AddHealth(newMonster->GetHealth() * multiply - newMonster->GetHealth());
		newMonster->AddMaxHealth(newMonster->GetMaxHealth( ) * multiply - newMonster->GetMaxHealth());
		newMonster->AddAttack(newMonster->GetAttack() * multiply - newMonster->GetAttack());
	}

	return newMonster;
}

