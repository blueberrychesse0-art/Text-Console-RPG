#include "Shop.h"
#include "../Character.h"
#include "Item.h"
#include "ItemManager.h"
#include "../../../FrameWork.h"



void Shop::ShowItems( ) const
{
	std::cout << "\n======== [ 상 점 ] ========" << std::endl;
	std::cout << "1. 체력 포션 (50G)" << std::endl;
	std::cout << "2. 공격력 포션 (50G)" << std::endl;
	std::cout << "3. 랜덤 박스 (10G)" << std::endl;
	std::cout << "4. 아이템 판매" << std::endl;
	std::cout << "0. 상점 나가기" << std::endl;
	std::cout << "=========================" << std::endl;
}

//1~3 아이템 구입
void Shop::BuyItem(Character* player , int choice) {
	if ( choice == 1 ) {
		if ( player->GetGold( ) >= 50 ) {
			player->UseGold(50);
			player->AddItem(ItemManager::getInstance()->CreateItem(ItemType::HealthPotion, 1));
			std::cout << "남은 골드: " << player->GetGold( ) << " G" << std::endl;
		}
		else {
			std::cout << "골드가 부족합니다." << std::endl;
		}
	}
	else if ( choice == 2 ) {
		if ( player->GetGold( ) >= 50 ) {
			player->UseGold(50);
			player->AddItem(ItemManager::getInstance()->CreateItem(ItemType::AttackBoost, 1));
			std::cout << "남은 골드: " << player->GetGold( ) << " G" << std::endl;
		}
		else {
			std::cout << "골드가 부족합니다." << std::endl;
		}
	}
	//랜덤박스. 체력 포션(10%), 공격력 포션(10%), 강화석(20%), 5G(20%), 꽝(40%)
	else if ( choice == 3 ) {
		if ( player->GetGold( ) >= 10 ) {
			player->UseGold(10);
			std::cout << "랜덤 박스 오픈!" << std::endl;
			std::random_device rd;
			std::mt19937 gen(rd( ));
			std::uniform_int_distribution<int> dis(1 , 100);
			int randNum = dis(gen);

			if ( randNum <= 10 ) {
				std::cout << "체력 포션 당첨!" << std::endl;
				player->AddItem(ItemManager::getInstance()->CreateItem(ItemType::HealthPotion, 1));
			}
			else if ( randNum <= 20 ) {
				std::cout << "공격력 포션 당첨!" << std::endl;
				player->AddItem(ItemManager::getInstance()->CreateItem(ItemType::AttackBoost, 1));
			}
			else if ( randNum <= 40 ) {
				std::cout << "강화석 당첨!" << std::endl;
				player->AddItem(ItemManager::getInstance()->CreateItem(ItemType::EnhancementStone, 1));
			}
			else if ( randNum <= 60 ) {
				std::cout << "5G 당첨!" << std::endl;
				player->AddGold(5);
			}
			else {
				std::cout << "꽝" << std::endl;
			}
		}
		else {
			std::cout << "골드가 없습니다. 돈을 벌어오세요." << std::endl;
		}
	}
	else if ( choice == 4 ) {
		int sellChoice = -1;
		while ( sellChoice != 0 ) {
			player->ShowInventory( );
			std::cout << "판매할 아이템 번호를 입력하세요(0. 뒤로가기) :" << std::endl;
			std::cin >> sellChoice;

			if ( sellChoice > 0 && sellChoice <= player->GetInventorySize( ) ) {
				int index = sellChoice - 1;
				Item* soldItem = player->GetItem(index);

				if ( soldItem != nullptr ) {
					int price = soldItem->GetSellPrice( );
					player->AddGold(price);
					soldItem->AddCount(-1);
					if ( soldItem->GetCount( ) <= 0 ) {
						player->RemoveItem(index);
					}
				}
			}
			else if ( sellChoice != 0 ) {
				std::cout << "잘못된 번호입니다." << std::endl;
			}
		}
	}

	else if ( choice != 0 ) {
		std::cout << "숫자를 다시 입력하세요." << std::endl;
	}
}

//OpenShop 함수 -> 전투루프 끝나고 상점 방문 시 호출.
void Shop::OpenShop(Character* player) {
	int choice = -1;
	while ( choice != 0 ) {
		ShowItems( );
		std::cout << "번호를 입력하세요: ";
		std::cin >> choice;

		if ( choice != 0 ) {
			BuyItem(player , choice);
		}
	}
}