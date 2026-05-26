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
	int GetLevel()const;
	int GetExperience()const;

	void AddGold(int amount);
	void UseGold(int amount);

	//Item* 해제 위한 소멸자, 인벤토리 기능
	~Character();
	void AddItem(Item* item);
	void ShowInventory( ) const;
	void SellItem(int index);
	void RemoveItem(int index);

	int GetInventorySize( ) const;

	Item* GetItem(int index) const;
};

