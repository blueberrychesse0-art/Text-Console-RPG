#pragma once


#include <string>

using namespace std;

class Monster
{
protected:
    string name;
    int health;
    int attack;

public:
    Monster(string name, int health, int attack);
    virtual ~Monster() {}

    string getName() const;
    int getHealth() const;
    int getAttack() const;

    void takeDamage(int damage);
    bool isDead() const;
};