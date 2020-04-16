#include "pch.h"
#include "EnemyManager.h"

#include "Enemy.h"

EnemyManager::EnemyManager()
	: m_Enemies{}
	, m_EnemiesToDelete{}
{
}
EnemyManager::~EnemyManager()
{
	Cleanup();
}

EnemyManager* EnemyManager::GetInstance()
{
	static EnemyManager* instance{ nullptr };
	if (instance == nullptr)
	{
		instance = &EnemyManager();
	}
	return instance;
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