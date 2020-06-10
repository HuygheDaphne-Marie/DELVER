#include "pch.h"
#include "MovementBehaviour.h"

MovementBehaviour::MovementBehaviour(Enemy* pEnemy)
	: m_pEnemy{pEnemy}
{
	if (m_pEnemy != nullptr)
	{
		Initialize();
	}
}
MovementBehaviour::~MovementBehaviour()
{
	m_pEnemy = nullptr;
}

void MovementBehaviour::Initialize()
{
}

void MovementBehaviour::SetEnemy(Enemy* enemy)
{
	if (enemy != nullptr && m_pEnemy == nullptr)
	{
		m_pEnemy = enemy;
		Initialize();
	}
}

