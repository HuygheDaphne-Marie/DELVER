#pragma once

class Enemy;
class Level;
class Bullet;
class Room;

#include <vector>
#include "LootDropper.h"

class EnemyManager final
{
public:
	Level* m_pCurrentLevel;

	EnemyManager(const EnemyManager& other) = delete;
	EnemyManager& operator=(const EnemyManager& other) = delete;
	EnemyManager(EnemyManager&& other) = delete;
	EnemyManager& operator=(EnemyManager&& other) = delete;
	~EnemyManager();

	static EnemyManager* GetInstance();

	void UpdateEnemies(float elapsedSec);
	void DrawEnemies() const;

	void AddEnemy(Enemy* enemy);

	void CheckCollision(Bullet* bulletToCheckWith);
	void QueueToDestroy(Enemy* enemy);

	void ClearAll();

	//void SpawnEnemiesForRoom(const Room* room);

private:
	EnemyManager();

	std::vector<Enemy*> m_Enemies;
	std::vector<Enemy*> m_EnemiesToDelete;

	LootDropper m_LootDropper;

	void Cleanup();
	void DestroyEnemiesInDestroyQueue();
};

