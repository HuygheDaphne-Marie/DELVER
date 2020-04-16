#include "pch.h"
#include "EnemyManager.h"

#include "Enemy.h"
#include "Bullet.h"

EnemyManager::EnemyManager()
	: m_Enemies{}
	, m_EnemiesToDelete{}
	, m_pCurrentLevel{nullptr}
{
}
EnemyManager::~EnemyManager()
{
	Cleanup();
}

EnemyManager* EnemyManager::GetInstance()
{
	static EnemyManager* instance;
	if (instance == nullptr)
	{
		instance = new EnemyManager();
	}
	return instance;
}

void EnemyManager::UpdateEnemies(float elapsedSec)
{
	if (m_pCurrentLevel == nullptr)
	{
		return; // Enemies need a level ref to update, so I can't allow an update without one.
	}

	for (Enemy* enemy : m_Enemies)
	{
		enemy->Update(elapsedSec, *m_pCurrentLevel);
	}
	DestroyEnemiesInDestroyQueue();
}
void EnemyManager::DrawEnemies() const
{
	for (Enemy* enemy : m_Enemies)
	{
		enemy->Draw();
	}
}

void EnemyManager::AddEnemy(Enemy* enemy)
{
	m_Enemies.push_back(enemy);
}

void EnemyManager::CheckCollision(Bullet* bulletToCheckWith)
{
	for (Enemy* enemy : m_Enemies)
	{
		if (enemy->isPointInCollisionRect(bulletToCheckWith->GetPosition()))
		{
			bulletToCheckWith->OnHit(enemy);
			return;
		}
	}
}
void EnemyManager::QueueToDestroy(Enemy* enemy)
{
	m_EnemiesToDelete.push_back(enemy);
}

void EnemyManager::Cleanup()
{
	for (std::vector<Enemy*>::iterator itr{m_Enemies.begin()}; itr != m_Enemies.end(); itr++)
	{
		delete (*itr);
		*itr = nullptr;
	}
	m_Enemies.clear();
	m_EnemiesToDelete.clear();
}
void EnemyManager::DestroyEnemiesInDestroyQueue()
{
	for (Enemy* enemy : m_EnemiesToDelete)
	{

		for (size_t idx{ 0 }; idx < m_Enemies.size(); idx++)
		{
			if (m_Enemies[idx] == enemy)
			{
				delete m_Enemies[idx];
				m_Enemies[idx] = m_Enemies[m_Enemies.size() - 1];
				idx--;
				m_Enemies.pop_back();
			}
		}

	}
	m_EnemiesToDelete.clear();
}