

#include "Monster.h"


Monster::Monster(string name, int health, int attack)
{
    this->name = name;
    this->health = health;
    this->attack = attack;
}

string Monster::getName() const
{
    return name;
}

int Monster::getHealth() const
{
    return health;
}

int Monster::getAttack() const
{
    return attack;
}

void Monster::takeDamage(int damage)
{
    health -= damage;

    if (health < 0)
    {
        health = 0;
    }
}

bool Monster::isDead() const
{
    return health <= 0;
}