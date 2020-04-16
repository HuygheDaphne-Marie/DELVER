#pragma once

class Enemy;

class EnemyManager final
{
public:
	EnemyManager(const EnemyManager& other) = delete;
	EnemyManager& operator=(const EnemyManager& other) = delete;
	EnemyManager(EnemyManager&& other) = delete;
	EnemyManager& operator=(EnemyManager&& other) = delete;
	~EnemyManager();

	static EnemyManager* GetInstance();

private:
	EnemyManager();

	std::vector<Enemy*> m_Enemies;
	std::vector<Enemy*> m_EnemiesToDelete;

	void Cleanup();
};

