#include "Item.h"

#include <iostream>
#include <vector>
#include <cstdlib>

std::vector<Item> inventory = {
	{"HP 포션", 50, 0, 10}, {"공격력 포션", 0, 10, 10}
};

//maxHP 있어야 할 것 같아요. 초과해서 회복하는 거 방지
//그리고 일단 currentHealth로 구현해봤습니다. 나중에 충돌하는 건 수정할게요.
void useItem(int& currentHealth, int maxHP, int& attack) {

	int randomidx = rand() % inventory.size();

	if (inventory[randomidx].count <= 0) {
		int otheridx = (randomidx == 0) ? 1 : 0;
		if (inventory[otheridx].count > 0) {
			randomidx = otheridx;
		}
		else {
			std::cout << "사용할 포션이 없습니다!!!" << std::endl;
			return;
		}
	}

	Item& selectedItem = inventory[randomidx];
	selectedItem.count--;

	std::cout << "\n" << selectedItem.name << "을 사용했습니다. (남은 개수: " << selectedItem.count << ")" << std::endl;

	if (selectedItem.healthRestore > 0) {
		currentHealth += selectedItem.healthRestore;
		if (currentHealth > maxHP) {
			currentHealth = maxHP;
			std::cout << "체력 회복 (현재 : " << currentHealth << ")" << std::endl;
		}
	}
	if (selectedItem.attackincrease > 0) {
		attack += selectedItem.attackincrease;
		std::cout << "공격력 증가 (현재 : " << attack << ")" << std::endl;
	}
}

//만약 공격과 아이템 사용 확률을 나누고 싶으면 전투 루프 안에서 해결하면 될 것 같고,
//아이템 사용시 다른 랜덤 공식을 사용할 지, 아니면 조건을 부여해줄 지는 나중에 정하면 좋을 것 같습니다.