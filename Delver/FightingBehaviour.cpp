#include "pch.h"
#include "FightingBehaviour.h"

#include "Enemy.h"

FightingBehaviour::FightingBehaviour(Enemy* pEnemy)
	: m_pEnemy{pEnemy}
{
	if (m_pEnemy != nullptr)
	{
		Initialize();
	}
}
FightingBehaviour::~FightingBehaviour()
{
	m_pEnemy = nullptr;
}

void FightingBehaviour::Initialize()
{
}

void FightingBehaviour::SetEnemy(Enemy* enemy)
{
	if (enemy != nullptr && m_pEnemy == nullptr)
	{
		m_pEnemy = enemy;
		Initialize();
	}
}