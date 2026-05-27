#pragma once
#include "EquipMent.h"

class Weapon : public EquipMent
{
public:
	Weapon(std::string name, Stats stats, int price = 10, int count = 1) : EquipMent(name , stats, price, count) {}

	void use(Character* character) override {}
};

