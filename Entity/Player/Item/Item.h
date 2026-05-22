#pragma once

#include <string>

class Character;

class Item {
protected:
	std::string name;
	int count;

public:
	//아이템 생성자
	Item(std::string itemName, int count)
		: name(name), count(count) {
	}

	virtual ~Item() {}

	std::string getName() const { return name; }

	virtual void use(Character* character) = 0;

};

//체력 회복 초기 count 5
class HealthPotion : public Item {
private:
	int healthRestore;

public:
	HealthPotion(std::string name, int healthRestore, int count = 5)
		: Item(name, count), healthRestore(healthRestore) {
	}

	void use(Character* character) override;

};

//공격력 증가 (임시로 공격력 영구적으로 10 증가). 초기 count 5
class AttackBoost : public Item {
private:
	int attackIncrease;

public:
	AttackBoost(std::string name, int attackincrease, int count = 5)
		: Item(name, count), attackIncrease(attackincrease) {
	}

	void use(Character* character) override;

};