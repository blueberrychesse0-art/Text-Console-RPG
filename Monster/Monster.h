#pragma once


#include "../Entity.h"
#include <string>


class Monster : public Entity
{
public:
    Monster(std::string name, int health, int attack);

    void Attack() override;
    void TakeDamage(int damage) override;

    bool IsDead() const;
};