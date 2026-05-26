#include "Character.h"
#include "Item/Item.h"	//아이템 헤더 추가
#include <iostream>

using namespace std;

Character::Character(std::string n):Entity(n, 200, 30)
{
	level = 1;
	experience = 0;
	gold = 0;
}
void Character::Attack()
{
	cout << name << "의 공격!" << endl;
}
void Character::TakeDamage(int damage)
{
	health -= damage;
}
void Character::DisplayStatus() const
{
	cout << "\n====================================" << endl;
	cout << name << "의 현재 상태" << endl;
	cout << "====================================" << endl;
	cout << "체력 : " << maxHealth << "/" << health << " | 공격력 : " << attack << endl
		<< "현재 레벨 : " << level << " | 경험치 : " << experience << "/100" << endl;
}
void Character::AddExperience(int amount)
{
	experience += amount;
	cout << "경험치 +" << amount << "획득! (" << experience << "/100)" << endl;

	while (experience >= 100 && level<10)
	{
		cout << "* 레벨업 조건 충족!" << endl;
		cout << "Lv." << level << "-> Lv.";
		level++;
		cout << level;
		experience -= 100;
		cout << " (" << experience << "/100)" << endl;

		maxHealth += level * 20;
		health = maxHealth;
		attack += level * 5;
		
		if (experience > 100)
		{
			cout << "(레벨업 후 남은 경험치는 다음 레벨 경험치에 반영됩니다.)" << endl;
		}
	}
}


int Character::GetGold()const
{
	return gold;
}
void Character::AddGold(int amount)
{
	gold += amount;
}
void Character::UseGold(int amount)
{
	gold -= amount;
}
int Character::GetLevel()const
{
	return level;
}
int Character::GetExperience()const
{
	return experience;
}

//int main() {
//	string temp;
//	cout << "이름을 입력하세요 : ";
//	cin >> temp;
//	Character MyCha(temp,200,30);
//	MyCha.DisplayStatus();
//}

//아이템 메모리 누수 방지
Character::~Character() {
	for (Item* item : inventory) {
		delete item;
	}
	inventory.clear( );
}

//인벤토리 기능 구현 위해서 추가, AddItem 함수가 호출될 때 중복 검사
void Character::AddItem(Item* newItem) {
	for ( Item* item : inventory ) {
		if ( item->getName() == newItem->getName()) {
			item->AddCount(newItem->getCount());

			std::cout << newItem->getName( ) << "을(를) 획득했습니다." << std::endl;
			delete newItem;
			return;
		}
	}
	inventory.push_back(newItem);
	std::cout << newItem->getName( ) << "을(를) 획득했습니다." << std::endl;
}

void Character::ShowInventory( ) const {
	std::cout << "현재 소지 골드 : " << gold << " G" << std::endl;
	std::cout << "=== [ 인벤토리 ] ===" << std::endl;
	
	if ( inventory.empty( ) ) {
		std::cout << "(비어 있음)" << std::endl;
		return;
	}
	for ( int i = 0; i < inventory.size( ); ++i ) {
		std::cout << i + 1 << ". " << inventory[i]->getName( ) << " (" << inventory[i]->getCount( ) << "개) "
			<< "(" << inventory[i]->getSellPrice( ) << " G" << std::endl;
	}
}

void Character::SellItem(int index) {
	if ( index < 0 || index >= inventory.size( ) ) {
		std::cout << "잘못된 번호를 입력했습니다." << std::endl;
		return;
	}
	Item* item = inventory[index];
	int sellPrice = item->getSellPrice( );

	AddGold(sellPrice);
	item->AddCount(-1);

}

void Character::RemoveItem(int index) {
	if ( index < 0 || index >= inventory.size( ) ) return;
	delete inventory[index];
	inventory.erase(inventory.begin( ) + index);
}

int Character::GetInventorySize( ) const {
	return inventory.size( );
}

Item* Character::GetItem(int index) const {
	if ( index < 0 || index >= inventory.size( ) ) return nullptr;
	return inventory[index];
}