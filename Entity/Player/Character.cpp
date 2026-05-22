#include "Character.h"
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

//int main() {
//	string temp;
//	cout << "이름을 입력하세요 : ";
//	cin >> temp;
//	Character MyCha(temp,200,30);
//	MyCha.DisplayStatus();
//}