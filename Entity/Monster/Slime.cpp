

#include "Slime.h"
#include <cstdlib>


Slime::Slime(int playerLevel)
    : Monster(
        "슬라임",
        playerLevel * 20 + rand() % (playerLevel * 10 + 1),
        playerLevel * 5 + rand() % (playerLevel * 5 + 1)
    )
{
	dropTable.push_back({ ItemType::HealthPotion, 0.3f });
	dropTable.push_back({ ItemType::EnhancementStone, 0.5f });
}