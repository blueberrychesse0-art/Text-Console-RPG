#include "Entity.h"
#include <string>

using namespace std;

Entity::Entity(std::string name, int health, int attack)
{
    this->name = name;
    this->health = health;
	this->maxHealth = health; // 현재는 안쓰지만 기믹 추가 할때를 대비해서 적어두었습니다. ex) 체력 회복 아이템, 몬스터가 체력을 회복하는 패턴 등
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
int Entity::GetMaxHealth()const
{
	return maxHealth;
}
void Entity::AddHealth(int amount)
{
	health += amount;
}
void Entity::AddAttack(int amount)
{
	attack += amount;
}
void Entity::AddMaxHealth(int amount)
{
	maxHealth += amount;
}
