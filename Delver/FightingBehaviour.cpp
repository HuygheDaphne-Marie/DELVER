#include "pch.h"
#include "FightingBehaviour.h"

#include "Enemy.h"

FightingBehaviour::FightingBehaviour(Enemy* pEnemy)
	: m_pEnemy{pEnemy}
{
}
FightingBehaviour::~FightingBehaviour()
{
	m_pEnemy = nullptr;
}