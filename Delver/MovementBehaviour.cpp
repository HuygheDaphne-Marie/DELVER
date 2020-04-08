#include "pch.h"
#include "MovementBehaviour.h"

MovementBehaviour::MovementBehaviour(Enemy* pEnemy)
	: m_pEnemy{pEnemy}
{
}
MovementBehaviour::~MovementBehaviour()
{
	m_pEnemy = nullptr;
}