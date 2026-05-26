#pragma once
#include "Character.h"
#include "Item/Item.h"	//아이템 헤더 추가
#include "Item/EquipMent/EquipMent.h"
#include "Item/EquipMent/Armor.h"
#include "Item/EquipMent/Weapon.h"
#include "../../FrameWork.h"

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
	if ( equip == nullptr )
	{
		std::cout << "장비 아이템이 아닙니다\n";
		return; // 장비아이템이 아니면

	}

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
		if ( item->GetName() == newItem->GetName()) {
			item->AddCount(newItem->GetCount());

			std::cout << newItem->GetName( ) << "을(를) 획득했습니다." << std::endl;
			delete newItem;
			return;
		}
	}
	inventory.push_back(newItem);
	std::cout << newItem->GetName( ) << "을(를) 획득했습니다." << std::endl;
}

void Character::ShowInventory( ) const {
	std::cout << "현재 소지 골드 : " << gold << " G" << std::endl;
	std::cout << "=== [ 인벤토리 ] ===" << std::endl;
	
	if ( inventory.empty( ) ) {
		std::cout << "(비어 있음)" << std::endl;
		return;
	}
	for ( int i = 0; i < inventory.size( ); ++i ) {
		std::cout << i + 1 << ". " << inventory[i]->GetName( ) << " (" << inventory[i]->GetCount( ) << "개) "
			<< "(" << inventory[i]->GetSellPrice( ) << " G" << std::endl;
	}
}

void Character::SellItem(int index) {
	if ( index < 0 || index >= inventory.size( ) ) {
		std::cout << "잘못된 번호를 입력했습니다." << std::endl;
		return;
	}
	Item* item = inventory[index];
	int sellPrice = item->GetSellPrice( );

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

bool Character::UseItemInBattle( ) {
	vector<int> usableItems;
	std::cout << "==== [ 사용 가능한 아이템 ] ====" << std::endl;

	int displayIndex = 1;
	for ( int i = 0; i < inventory.size( ); ++i ) {
		if ( inventory[i]->isUsableInBattle( ) ) {
			cout << displayIndex << ". " << inventory[i]->GetName( ) << " (" << inventory[i]->GetCount( ) << "개)" << std::endl;
		
			usableItems.push_back(i);
			displayIndex++;
		}
	}
	if ( usableItems.empty( ) ) {
		cout << "(비어 있음)" << endl;
		return false;
	}

	std::cout << "0. 뒤로 가기" << std::endl;
	std::cout << "사용할 아이템 번호를 입력하세요: ";
	int itemChoice;
	cin >> itemChoice;

	if ( itemChoice == 0 ) {
		return false;
	}

	if ( itemChoice > 0 && itemChoice < displayIndex ) {
		int targetInventoryIndex = usableItems[itemChoice - 1];
		Item* selectedItem = inventory[targetInventoryIndex];

		selectedItem->use(this);

		if ( selectedItem->GetCount( ) <= 0 ) {
			RemoveItem(targetInventoryIndex);
		}
		return true;
	}

	std::cout << "번호를 다시 입력하세요." << std::endl;
	return false;
}

bool Character::UseEnhancementStone( )
{
	for ( auto it = inventory.begin( ); it != inventory.end( ); ++it ) {
		
		if ( ( *it )->GetName( ) == "강화석" ) {
			
			delete* it;
			inventory.erase(it);
			return true; 
		}
	}
	return false; 

}