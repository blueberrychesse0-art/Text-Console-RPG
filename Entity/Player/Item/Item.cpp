#include "Item.h"
#include "../Character.h"
#include <iostream>

void HealthPotion::use(Character* character) {
	//포션이 0개 이하이면 사용 못하게 했고
	if (count <= 0) {
		std::cout << "체력 포션이 없습니다." << std::endl;
		return;
	}

	//사용시 개수를 감소하게 했습니다.
	count--;

	character->health += healthRestore;
	if (character->health > character->maxHealth) {
		character->health = character->maxHealth;
	}

	std::cout << "체력 회복 (현재 : " << character->health << ")" << std::endl;
}

void AttackBoost::use(Character* character) {
	if (count <= 0) return;

	count--;

	character->attack += attackIncrease;

	std::cout << "공격력 증가 (현재 : " << character->attack << ")" << std::endl;
}
