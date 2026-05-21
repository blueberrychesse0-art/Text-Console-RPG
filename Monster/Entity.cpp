#include "Entity.h"
#include <string>

using namespace std;

Entity::Entity(std::string name, int health, int attack)
{
    this->name = name;
    this->health = health;
    this->maxHealth = health;
    this->attack = attack;
}


string Entity::GetName()const
{
	return name;
}
int Entity::GetHealth()const
{
	return health;
}
int Entity::GetAttack()const
{
	return attack;
}