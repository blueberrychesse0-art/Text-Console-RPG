#pragma once
#include <string>



class Entity
{
protected:
	std::string name;
	int health;
	int maxHealth;
	int attack;

public:	//퍼블릭 중복 있어서 지웠습니다.
	Entity(std::string name, int health, int attack);
	virtual ~Entity() {}

	virtual void Attack() = 0;
	virtual void TakeDamage(int damage) = 0;

	std::string GetName()const;
	int GetHealth()const;
	virtual int GetAttack( )const; // 캐릭터 장비 스탯을 위해 가상화virtual
	virtual int GetMaxHealth( )const; // 캐릭터 장비 스탯을 위해 가virtual상화

	void AddHealth(int amount);
	void AddAttack(int amount);
	void AddMaxHealth(int amount);
};

