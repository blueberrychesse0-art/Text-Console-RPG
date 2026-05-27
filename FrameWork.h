#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <math.h>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct Stats
{
	int health;
	int atk;
	int lv;
};

enum class ItemType {
	HealthPotion ,
	AttackBoost ,
	EnhanceStone ,
	Weapon ,
	Armor
};

struct DropInfo
{
	ItemType type;
	float chance;
};