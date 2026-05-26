#pragma once
#include "EquipMent.h"

class Weapon : public EquipMent
{
public:
	Weapon(std::string name , Stats stats , int count = 1) : EquipMent(name , stats) {}
};

