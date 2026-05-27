#include "ItemManager.h"
#include "Item.h"
#include "Equipment/Weapon.h"
#include "EquipMent/Armor.h"

ItemManager* ItemManager::instance = nullptr;

ItemManager* ItemManager::getInstance( ) {
	if ( instance == nullptr ) {
		instance = new ItemManager( );
	}
	return instance;
}

Item* ItemManager::CreateItem(ItemType type , int count) {

	//Stats {health, atk, lv}
	Stats baseWeaponStats = { 0, 20, 1 };
	Stats baseArmorStats = { 50, 0, 1 };

	switch ( type ) {

	case ItemType::HealthPotion:
		return new HealthPotion("체력 포션" , 50 , count, 50);

	case ItemType::AttackBoost:
		return new AttackBoost("공격력 포션" , 10 , count, 50);

	case ItemType::EnhancementStone:
		return new EnhancementStone("강화석" , count, 20);

	case ItemType::Weapon:
		return new Weapon("검" , baseWeaponStats, 100, count);

	case ItemType::Armor:
		return new Armor("갑옷" , baseArmorStats, 100, count);

	default:
		return nullptr;
	}
}