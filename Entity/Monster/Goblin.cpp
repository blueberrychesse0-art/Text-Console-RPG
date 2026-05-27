

#include "Goblin.h"
#include <cstdlib>


Goblin::Goblin(int playerLevel)
    : Monster(
        "고블린",
        playerLevel * 20 + rand() % (playerLevel * 10 + 1),
        playerLevel * 5 + rand() % (playerLevel * 5 + 1)
    )
{
	dropTable.push_back({ ItemType::HealthPotion, 0.5f });
	dropTable.push_back({ ItemType::EnhanceStone, 0.5f });
}