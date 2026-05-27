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
	int GetCount() const { return count; }

	void AddCount(int amount) { count += amount; }
	
	//아이템 이름 반환
	std::string GetName() const { return name; }

	//아이템 판매를 위한 가상 함수 추가
	virtual int GetSellPrice( ) const { return 1; }

	//사용 가능한 아이템만 전투 중 인벤토리에 출력하기 위해 가상함수 추가
	virtual bool isUsableInBattle( ) const { return false; }

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
	bool isUsableInBattle( ) const override { return true; }

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
	bool isUsableInBattle( ) const override { return true; }
};

//강화석
class EnhancementStone : public Item {
public:
	EnhancementStone(std::string name , int count, int price)
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

	int GetAttackPower( ) const { return attackPower; }
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

	int GetArmorHealth( ) const { return armorHealth; }
};