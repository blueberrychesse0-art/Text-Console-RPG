#pragma once
#include "../Entity.h"
#include "../../FrameWork.h"

class Weapon;
class Armor;

struct Item;

class Character : public Entity
{
private:
	int level;
	int experience;
	int gold;
	std::vector<Item*> inventory;
	Weapon* equippedWeapon = nullptr;
	Armor* equippedArmor = nullptr;
public:
	Character(std::string n);

	void Attack() override;
	void TakeDamage(int damage) override;
	void DisplayStatus()const;
	void AddExperience(int amount);
	
	
	int GetGold()const;
	int GetLevel()const;
	int GetExperience()const;
	int GetAttack( )const override; // 무기 공격력을 포함한 공격력
	int GetMaxHealth( )const override; // 갑옷 체력을 포함한 최대 체력

	Weapon* GetEquippedWeapon( ) const;
	Armor* GetEquippedArmor( ) const;

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

	void Equip(int inventoryIndex);	// 장비 장착

};

