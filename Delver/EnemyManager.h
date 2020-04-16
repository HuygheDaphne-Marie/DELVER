#pragma once

class Enemy;
class Level;
class Bullet;

#include <vector>

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

private:
	EnemyManager();

	std::vector<Enemy*> m_Enemies;
	std::vector<Enemy*> m_EnemiesToDelete;

	void Cleanup();
	void DestroyEnemiesInDestroyQueue();
};

