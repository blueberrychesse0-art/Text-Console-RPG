
#include "Monster.h"
#include <iostream>


using namespace std;


Monster::Monster(std::string name, int health, int attack)
    : Entity(name, health, attack)
{

}

void Monster::Attack()
{
    cout << name << "이(가) 공격합니다! 공격력: " << attack << endl;
}

void Monster::TakeDamage(int damage)
{
    health -= damage;

    if (health < 0)
    {
        health = 0;
    }

    cout << name << "이(가) " << damage << " 데미지를 받았습니다. 현재 체력: "
        << health << endl;
}

bool Monster::IsDead() const
{
    return health <= 0;
}