#pragma once
#include "../FrameWork.h"
#include "../Entity/Entity.h"
#include "../Entity/Player/Character.h"
#include "../Entity/Monster/Goblin.h"
#include "../Entity/Monster/Orc.h"
#include "../Entity/Monster/Slime.h"
#include "../Entity/Monster/Troll.h"

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
	void EncounterBoss();
	Monster* SpawnRandomMonsters(float multiply);
};

