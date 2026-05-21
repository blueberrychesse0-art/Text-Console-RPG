#pragma once

#include ".h"

#include <string>

struct Item {
	std::string name;
	int healthRestore;
	int attackincrease;
	int count;
};

void useItem(int& currentHealth, int maxHP, int& attack);