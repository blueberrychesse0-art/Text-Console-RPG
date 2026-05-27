

#include "Troll.h"
#include <cstdlib>


Troll::Troll(int playerLevel)
    : Monster(
        "트롤",
        playerLevel * 20 + rand() % (playerLevel * 10 + 1),
        playerLevel * 5 + rand() % (playerLevel * 5 + 1)
    )
{
	dropTable.push_back({ ItemType::Armor, 0.5f });
	dropTable.push_back({ ItemType::EnhancementStone, 0.5f });
}