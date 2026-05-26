#pragma once
#include "EquipMent.h"

class Armor : public EquipMent
{
public:
	Armor(std::string name , Stats stats , int count = 1) : EquipMent(name , stats) {}
};

