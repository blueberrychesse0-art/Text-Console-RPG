

#include "Orc.h"
#include <cstdlib>


Orc::Orc(int playerLevel)
    : Monster(
        "오크",
        playerLevel * 20 + rand() % (playerLevel * 10 + 1),
        playerLevel * 5 + rand() % (playerLevel * 5 + 1)
    )
{
	dropTable.push_back({ ItemType::Weapon, 0.5f });
	dropTable.push_back({ ItemType::EnhanceStone, 0.5f });
}