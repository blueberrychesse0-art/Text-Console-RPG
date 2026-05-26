#pragma once
#include "EquipMent.h"

class Armor : public EquipMent
{
public:
	Armor(std::string name , Stats stats , int price = 10 , int count = 1) : EquipMent(name , stats , price) {}
};

