#pragma once
#include "../FrameWork.h"
#include "../Entity/Entity.h"
#include "../Entity/Player/Character.h"
#include "../Entity/Monster/Goblin.h"
#include "../Entity/Monster/Orc.h"
#include "../Entity/Monster/Slime.h"
#include "../Entity/Monster/Troll.h"
#include "../Entity/Player/Item/EquipMent/Weapon.h"
#include "../Entity/Player/Item/EquipMent/Armor.h"

enum class BattleMode //전투 처음시작은 자동/ 이후는 수동으로 처리
{
	Auto ,
	Manual
};

class GameManager
{
private:
	static GameManager* instance;
	GameManager() {};
	~GameManager();
	Character* player = nullptr;
	std::vector<Monster*> monsters;
	std::mt19937 engine;
public:
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	
	static GameManager* getInstance();

	void Init();
	void Release();
	void CreatePlayer();
	void Main();
	void Battle();
	void Battle(BattleMode mode);
	Monster* SpawnRandomMonsters();
	bool IsEnchantSuccess(int currentLv);
	void EncounterBoss();
	Monster* SpawnRandomMonsters(float multiply);

};

