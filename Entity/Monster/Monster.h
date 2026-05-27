#pragma once

#include "../Entity.h"
#include "../../FrameWork.h"

class Monster : public Entity
{
protected:
	std::vector<DropInfo> dropTable;
public:
    Monster(std::string name, int health, int attack);

    void Attack() override;
    void TakeDamage(int damage) override;

    bool IsDead() const;
	std::vector<DropInfo> GetDropTable( ) { return dropTable; }

};