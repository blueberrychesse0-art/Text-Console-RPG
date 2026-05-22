#pragma once
#include "../Entity.h"
#include <vector>

struct Item;

class Character : public Entity
{
private:
	int level;
	int experience;
	int gold;
	std::vector<Item*> inventory;
public:
	Character(std::string n);

	void Attack() override;
	void TakeDamage(int damage) override;
	void DisplayStatus()const;
	void AddExperience(int amount);
	
	
	int GetGold()const;

	void AddGold(int amount);
	void UseGold(int amount);

};

