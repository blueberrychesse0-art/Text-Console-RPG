#include "Character.h"


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
	cout << "체력 : " << health << "/" << Character::GetMaxHealth( ) << " | 공격력 : " << Character::GetAttack() << endl
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

void Character::Equip(int inventoryIndex)
{
	if ( inventoryIndex < 0 || inventoryIndex >= inventory.size( ) )return;	// 인벤토리에 없는 아이템을 가져오려 한다면

	Item* item = inventory[inventoryIndex];
	EquipMent* equip = dynamic_cast<EquipMent*>(item);
	if ( equip == nullptr )return; // 장비아이템이 아니면

	Weapon* weapon = dynamic_cast< Weapon* >(equip);	// 무기인지 판독
	if ( weapon != nullptr )
	{
		inventory.erase(inventory.begin( ) + inventoryIndex); // 인벤토리에서 무기 제거
		if ( equippedWeapon != nullptr )	// 무기가 장착중이라면
		{
			inventory.push_back(equippedWeapon);	// 인벤토리에 넣고
		}
		equippedWeapon = weapon;	// 무기 교체
		
		cout << weapon->GetName( ) << "(무기)을 장착했습니다.\n"; // 아이템 GetName 만들어져야함
		return;
	}

	Armor* armor = dynamic_cast< Armor* >( equip );	// 갑옷인지 판독
	if ( armor != nullptr )
	{
		inventory.erase(inventory.begin( ) + inventoryIndex); // 인벤토리에서 갑옷 제거
		if ( equippedArmor != nullptr )	// 갑옷이 장착중이라면
		{
			inventory.push_back(equippedArmor);	// 인벤토리에 넣고
		}
		equippedArmor = armor;	// 갑옷 교체
		
		cout << armor->GetName() << "(방어구)을 장착했습니다.\n"; // 아이템 GetName 만들어져야함
		return;
	}
}
int Character::GetAttack()const 
{
	int totalAtk = Entity::GetAttack( );
	if ( equippedWeapon != nullptr )
	{
		totalAtk += equippedWeapon->GetStats( ).atk;
	}
	return totalAtk;
}
int Character::GetMaxHealth( )const
{
	int totalHP = Entity::GetMaxHealth( );
	if ( equippedArmor != nullptr )
	{
		totalHP += equippedArmor->GetStats( ).health;
	}
	return totalHP;
}
Weapon* Character::GetEquippedWeapon( )const
{
	return equippedWeapon;
}
Armor* Character::GetEquippedArmor( )const
{
	return equippedArmor;
}

//int main() {
//	string temp;
//	cout << "이름을 입력하세요 : ";
//	cin >> temp;
//	Character MyCha(temp,200,30);
//	MyCha.DisplayStatus();
//}