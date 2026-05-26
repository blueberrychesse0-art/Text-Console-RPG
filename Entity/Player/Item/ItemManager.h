#pragma once

class Item;

enum class ItemType {
	HealthPotion,
	AttackBoost,
	EnhanceStone,
	BaseSword,
	BaseArmor
};

class ItemManager {
private:
	static ItemManager* instance;
	ItemManager( ) {}

public:
	static ItemManager* getInstance( );

	Item* CreateItem(ItemType type , int count = 1);
};