#include "GameManager.h"
#include "../Entity/Player/Item/ItemManager.h"
#include "../Entity/Player/Item/Shop.h"

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

	//나중에 삭제하시면 됩니다(치트).
	if ( name == "돈내놔" ) {
		std::cout << "100000G, 갑옷 한개, 무기 한개" << std::endl;

		player->AddGold(1000000);
		
		Item* addStones = ItemManager::getInstance( )->CreateItem(ItemType::EnhancementStone , 1000);
		if ( addStones != nullptr ) { player->AddItem(addStones); }

		Item* addArmor = ItemManager::getInstance( )->CreateItem(ItemType::Armor , 1);
		if ( addArmor != nullptr ) { player->AddItem(addArmor); }

		Item* addWeapon = ItemManager::getInstance( )->CreateItem(ItemType::Weapon , 1);
		if ( addWeapon != nullptr ) { player->AddItem(addWeapon); }
	}
	//여기까지가 치트

	Battle(BattleMode::Auto);
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
		std::cout << "2. 상점 방문" << std::endl;
		std::cout << "3. 대장간 방문" << std::endl;
		std::cout << "4. 인벤토리 확인" << std::endl;
		std::cout << "0. 게임 종료" << std::endl;

		player->DisplayStatus();

		std::cout << "\n선택 : ";
		std::cin >> select;

		switch ( select )
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
			Battle(BattleMode::Manual);
			break;
		case 2: 
		{
			Shop shop;
			shop.OpenShop(player);

			break;
		}
		case 3:
		{
			int smithySelect = -1;
			bool isExit = false;
			std::cout << "=======================================\n";
			std::cout << "[FORGE] 대장간 : 장비를 강화할 수 있습니다.\n";
			std::cout << "=======================================\n";
			while ( 1 )
			{

				std::cout << "1. 무기 강화 (공격력 상승)\n";
				std::cout << "2. 방어구 강화 (최대 체력 상승)\n";
				std::cout << "3. 장비 장착하기\n";
				std::cout << "0. 대장간 나가기\n";
				std::cout << "선택 : ";
				std::cin >> smithySelect;
				switch ( smithySelect )
				{
				case 1:
				{
					Weapon* currentWeapon = player->GetEquippedWeapon( );
					if ( currentWeapon == nullptr )
					{
						std::cout << "현재 장착 중인 무기가 없습니다! 먼저 무기를 장착하세요.\n";
						break;
					}
					
					int currentGold = player->GetGold( );
					Stats weaponStats = currentWeapon->GetStats( );
					int currentLv = weaponStats.lv;
					int cost = 100 * currentLv;

					if ( currentGold >= cost )
					{
						if ( player->UseEnhancementStone( ) == false )
						{
							std::cout << "인벤토리에 [강화석]이 없습니다!\n";
							break;
						}
						player->UseGold(cost);

						if ( IsEnchantSuccess(currentLv) == true )
						{
							std::cout << "강화 성공!\n";
							weaponStats.lv = currentLv + 1;
							weaponStats.atk += 10;

							currentWeapon->SetStats(weaponStats);
							break;
						}
						else
						{
							std::cout << "강화 실패!\n";
							break;
						}



					}
					else
					{
						std::cout << "골드가 부족합니다! (필요한 골드 : " << cost << "G)\n";
						break;
					}
				}
				case 2:
				{
					Armor* currentArmor = player->GetEquippedArmor( );
					if ( currentArmor == nullptr )
					{
						std::cout << "현재 장착 중인 갑옷이 없습니다! 먼저 갑옷을 장착하세요.\n";
						break;
					}
					
					int currentGold = player->GetGold( );
					Stats armorStats = currentArmor->GetStats( );
					int currentLv = armorStats.lv;
					int cost = 100 * currentLv;

					if ( currentGold >= cost )
					{
						if ( player->UseEnhancementStone( ) == false )
						{
							std::cout << "인벤토리에 [강화석]이 없습니다!\n";
							break;
						}
						player->UseGold(cost);

						if ( IsEnchantSuccess(currentArmor->GetStats( ).lv) == true )
						{
							std::cout << "강화 성공!\n";
							armorStats.lv = currentLv + 1;
							armorStats.health += 10;

							currentArmor->SetStats(armorStats);
							break;
						}
						else
						{
							std::cout << "강화 실패!\n";
							break;
						}
					}
					else
					{
						std::cout << "골드가 부족합니다! (필요한 골드 : " << cost << "G)\n";
						break;
					}
					break;
				}
				case 3:
				{
					int inventoryNum = -1;
					player->ShowInventory( );
					std::cout << "장착할 장비의 번호를 알려주세요 :";
					std::cin >> inventoryNum;
					player->Equip(inventoryNum);
					break;
				}
				case 0:
					isExit = true;
					break;
				default:
					break;
				}
				if ( isExit )
				{
					break;
				}
			}
			break;
		}
		case 4:
			player->ShowInventory();
			break;
			default:
				break;
		}
	}
	
}

void GameManager::Battle(BattleMode mode)
{
	int select = 0;

	// 몬스터가 없으면 실행하지 않음
	if ( monsters.empty( ) || monsters[0] == nullptr || player == nullptr )
		return;

	if ( mode == BattleMode::Auto )      //자동 전투
	{
		while ( player->GetHealth( ) > 0 && !monsters.empty( ) )
		{
			// 플레이어의 공격
			player->Attack( );
			monsters[0]->TakeDamage(player->GetAttack( ));

			if ( monsters[0]->GetHealth( ) <= 0 )			// 몬스터가 죽었을 시
			{
				std::cout << "\n전투 승리! " << std::endl;

				std::uniform_int_distribution<int> dist(10 , 21);		// 10 <= x < 21 
				int money = dist(engine);
				player->AddGold(money);
				std::cout << "골드 " << money << " 획득!" << std::endl;

				
				player->AddExperience(50);

				std::vector<DropInfo> dropTable = monsters[0]->GetDropTable( );
				std::uniform_real_distribution<float> dropDistribution(0.0f , 1.0f);

				for ( const auto& drop : dropTable ) {
					if ( dropDistribution(engine) <= drop.chance ) {
						Item* dropItem = ItemManager::getInstance( )->CreateItem(drop.type , 1);

						if ( dropItem != nullptr ) {
							player->AddItem(dropItem);
						}
					}
				}

				for ( Monster* m : monsters )
				{
					delete m;
				}
				monsters.clear( );
				return;
			}

			std::cout << std::endl;
			// 몬스터의 공격
			monsters[0]->Attack( );
			player->TakeDamage(monsters[0]->GetAttack( ));

			if ( player->GetHealth( ) <= 0 )			// 플레이어가 죽었을 시
			{
				std::cout << "전투 패배! " << std::endl;
				for ( Monster* m : monsters )
				{
					delete m;
				}
				monsters.clear( );
				return;//메인메뉴로
			}
		}
	}
	else  // 수동 전투
	{
		while ( player->GetHealth( ) > 0 && !monsters.empty( ) )
		{
			std::cout << "1. 공격하기" << std::endl;
			std::cout << "2. 아이템 사용" << std::endl;
			std::cout << "3. 도망가기" << std::endl;
			std::cin >> select;

			switch ( select )
			{
			case 1: // 공격하기
			{
				int preHealth = monsters[0]->GetHealth( );		// 공격 받기 전 체력

				// 플레이어의 공격
				player->Attack( );
				monsters[0]->TakeDamage(player->GetAttack( ));

				if ( monsters[0]->GetHealth( ) <= 0 )			// 몬스터가 죽었을 시
				{
					std::cout << "\n전투 승리! " << std::endl;

					std::uniform_int_distribution<int> dist(10 , 21);		// 10 <= x < 21 

					int money = dist(engine);
					player->AddGold(money);			// 골드 추가
					std::cout << "골드 " << money << " 획득!" << std::endl;

					player->AddExperience(50);		// 경험치 추가

					std::vector<DropInfo> dropTable = monsters[0]->GetDropTable( );
					std::uniform_real_distribution<float> dropDistribution(0.0f , 1.0f);

					for ( const auto& drop : dropTable ) {
						if ( dropDistribution(engine) <= drop.chance ) {
							Item* dropItem = ItemManager::getInstance( )->CreateItem(drop.type , 1);

							if ( dropItem != nullptr ) {
								player->AddItem(dropItem);
							}
						}
					}

					for ( Monster* m : monsters )
					{
						delete m;
					}
					monsters.clear( );
					return;
				}

				std::cout << std::endl;
				// 몬스터의 공격
				preHealth = player->GetHealth( );
				monsters[0]->Attack( );
				player->TakeDamage(monsters[0]->GetAttack());
				std::cout << player->GetName( ) << " 가 공격을 받았습니다. 현재 체력 : " << player->GetHealth() << std::endl;

				if ( player->GetHealth( ) <= 0 )			// 플레이어가가 죽었을 시
				{
					std::cout << "전투 패배! " << std::endl;
					for ( Monster* m : monsters )
					{
						delete m;
					}
					monsters.clear( );
					return;
				}
				break;
			}
			case 2: // 아이템 사용
				player->UseItemInBattle();

				break;
			case 3: // 도망 (메인메뉴로)
				std::cout << "도망치기!" << std::endl;
				for ( Monster* m : monsters )
				{
					delete m;
				}
				monsters.clear( );
				return;

			default:
				std::cout << "잘못된 입력입니다." << std::endl;
				break;
			}
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

			std::vector<DropInfo> dropTable = monsters[0]->GetDropTable( );
			std::uniform_real_distribution<float> dropDistribution(0.0f , 1.0f);

			for ( const auto& drop : dropTable ) {
				if ( dropDistribution(engine) <= drop.chance ) {
					Item* dropItem = ItemManager::getInstance( )->CreateItem(drop.type , 1);

					if ( dropItem != nullptr ) {
						player->AddItem(dropItem);
					}
				}
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

bool GameManager::IsEnchantSuccess(int currentLv)
{
	std::map<int , int> successRates =
	{
		{0,100},
		{1,90},
		{2,70},
		{3,40},
	};

	int rate = 0;
	if ( successRates.find(currentLv) != successRates.end())	// 4단계 이상은 10퍼센트(임시)
	{
		rate = successRates[currentLv];
	}
	else
	{
		rate = 10;
	}

	std::srand(std::time(nullptr));
	int random_number = std::rand( ) % 100 + 1;
	if ( random_number <= rate )
	{
		return true;
	}
	else
	{
		return false;
	}
}
