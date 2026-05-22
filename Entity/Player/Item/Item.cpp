#include "Item.h"
#include "Character.h"
#include <iostream>

void HealthPotion::use(Character* character) {
	//우선 health를 사용해서 작성, character.h에 #include "Item.h", Character.h에서 public으로 열어주세요(아니면 getter setter)
	character->health += healthRestore;

	if (character->health > character->maxHealth) {
		character->health = character->maxHealth;
	}

	std::cout << "체력 회복 (현재 : " << character->health << ")" << std::endl;
}

void AttackBoost::use(Character* character) {
	character->attack += attackIncrease;

	std::cout << "공격력 증가 (현재 : " << character->attack << ")" << std::endl;
}