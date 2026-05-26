#pragma once
#include "../Item.h"
#include "../../../../FrameWork.h"

class EquipMent : public Item
{
protected:
	Stats stats;
public:
	EquipMent(std::string name , Stats stats , int price = 10, int count = 1) : Item(name , count, price) , stats(stats) {};
	Stats GetStats() { return stats; }
	void SetStats(Stats stats) { this->stats = stats; }
	void SetLevel(int lv) { stats.lv = lv; }
};

