#pragma once

class GameManager
{
private:
	static GameManager* instance;
	GameManager() {};
	~GameManager();
public:
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	
	static GameManager* getInstance();

	void Init();
	void Main();
	void CreatePlayer();
};

