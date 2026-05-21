#pragma once
#include <string>



class Entity
{
protected:
	std::string name;
	int health;
	int maxHealth;
	int attack;
public:
	virtual ~Entity() {}

	virtual void Attack() = 0;
	virtual void TakeDamage(int damage) = 0;

	std::string GetName()const;
	int GetHealth()const;
	int GetAttack()const;
};

