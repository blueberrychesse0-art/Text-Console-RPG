#include "ItemManager.h"
#include "Item.h"

ItemManager* ItemManager::instance = nullptr;

ItemManager* ItemManager::getInstance( ) {
	if ( instance == nullptr ) {
		instance = new ItemManager( );
	}
	return instance;
}

Item* ItemManager::CreateItem(ItemType type , int count) {
	switch ( type ) {

	case ItemType::HealthPotion:
		return new HealthPotion("체력 포션" , 50 , count);

	case ItemType::AttackBoost:
		return new AttackBoost("공격력 포션" , 10 , count);

	case ItemType::EnhanceStone:
		return new EnhanceStone("강화석" , count);

	case ItemType::BaseSword:
		return new BaseSword("기본 검" , 20,  100);

	case ItemType::BaseArmor:
		return new BaseArmor("기본 갑옷" , 50,  100);



	}
}