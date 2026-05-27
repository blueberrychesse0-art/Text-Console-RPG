#pragma once
#include "../../../FrameWork.h"

class Item;

class ItemManager {
private:
	static ItemManager* instance;
	ItemManager( ) {}

public:
	static ItemManager* getInstance( );

	Item* CreateItem(ItemType type , int count = 1);
};