#include "Item.h"
#include "../Character.h"
#include <iostream>

void HealthPotion::use(Character* character) {

	if (count <= 0) {
		std::cout << "체력 포션이 없습니다." << std::endl;
		return;
	}

	count--;

	//변수를 선언 하고 getter함수 호출

	int currentHealth = character->GetHealth();
	int maxHealth = character->GetMaxHealth();

	//함수 수정(Entity.h의 AddHealth 함수 활용)
	if (currentHealth + healthRestore > maxHealth) {
		character->AddHealth(maxHealth - currentHealth);
	}
	else {
		character->AddHealth(healthRestore);
	}

	std::cout << "체력 회복 (현재 : " << character->GetHealth() << ")" << std::endl;
}

void AttackBoost::use(Character* character) {
	if (count <= 0) return;
	count--;

	//마찬가지로 Entity.h의 AddAttack 함수 활용
	character->AddAttack(attackIncrease);

	std::cout << "공격력 증가 (현재 : " << character->GetAttack() << ")" << std::endl;
}

void EnhanceStone::use(Character* character) {
	if ( count <= 0 ) return;
	count--;

	std::cout << "무기 장착 시스템, 강화 시스템 추가 예정" << std::endl;
}
