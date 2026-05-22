#include "Character.h"
#include <iostream>

using namespace std;

Character::Character(std::string n, int health, int attack):Entity(n, health, attack)
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


//int main() {
//	string temp;
//	cout << "이름을 입력하세요 : ";
//	cin >> temp;
//	Character MyCha(temp,200,30);
//	MyCha.DisplayStatus();
//}