#pragma once

class Item;

enum class ItemType {
	HealthPotion,
	AttackBoost,
	EnhancementStone,
	Weapon,
	Armor
};

class ItemManager {
private:
	static ItemManager* instance;
	ItemManager( ) {}

public:
	static ItemManager* getInstance( );

	Item* CreateItem(ItemType type , int count = 1);
};