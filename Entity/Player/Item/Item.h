#pragma once
#include "../../../FrameWork.h"

class Character;

class Item {
protected:
	std::string name;
	int count;
	int sellPrice;

public:
	//아이템 생성자
	Item(std::string itemName, int count, int price)
		: name(itemName), count(count), sellPrice(price) {
	}

	virtual ~Item() {}

	virtual void use(Character* character) = 0;
	int getCount() const { return count; }

	void AddCount(int amount) { count += amount; }
	
	//아이템 이름 반환
	std::string getName() const { return name; }

	//아이템 판매를 위한 가상 함수 추가
	virtual int getSellPrice( ) const { return 1; }

};

//체력 회복 초기 count 5
class HealthPotion : public Item {
private:
	int healthRestore;

public:
	HealthPotion(std::string name, int healthRestore, int count, int price)
		: Item(name, count, price), healthRestore(healthRestore) {
	}

	void use(Character* character) override;

};

//공격력 증가 (임시로 공격력 영구적으로 10 증가). 초기 count 5
class AttackBoost : public Item {
private:
	int attackIncrease;

public:
	AttackBoost(std::string name, int attackincrease, int count, int price)
		: Item(name, count, price), attackIncrease(attackincrease) {
	}

	void use(Character* character) override;

};

//강화석
class EnhanceStone : public Item {
public:
	EnhanceStone(std::string name , int count, int price)
		: Item(name , count, price) {
	}
	void use(Character* character) override;
};

class BaseSword : public Item {
private:
	int attackPower;

public:
	BaseSword(std::string name , int attackPower , int count , int price)
		: Item(name , count , price) , attackPower(attackPower) {
	}

	void use(Character* character) override {
		std::cout << "검을 장착했습니다." << std::endl;
	}

	int getAttackPower( ) const { return attackPower; }
};

class BaseArmor : public Item {
private:
	int armorHealth;

public:
	BaseArmor(std::string name , int armorHealth , int count , int price)
		: Item(name , count , price) , armorHealth(armorHealth) {
	}

	void use(Character* character) override {
		std::cout << "갑옷을 장착했습니다." << std::endl;
	}

	int getArmorHealth( ) const { return armorHealth; }
};