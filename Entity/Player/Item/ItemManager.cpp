#include "ItemManager.h"
#include "Item.h"
#include "Equipment/Weapon.h"
#include "EquipMent/Armor.h"
#include "EquipMent/Equipment.h"

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
		return new HealthPotion("체력 포션" , 50 , count, 50);

	case ItemType::AttackBoost:
		return new AttackBoost("공격력 포션" , 10 , count, 50);

	case ItemType::EnhanceStone:
		return new EnhanceStone("강화석" , count, 20);

	case ItemType::Weapon:
		return new BaseSword("기본 검" , 20, count, 100);

	case ItemType::Armor:
		return new BaseArmor("기본 갑옷" , 50, count, 100);

	default:
		return nullptr;
	}
}