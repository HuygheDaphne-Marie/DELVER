#include "pch.h"
#include "FightingBehaviour.h"

class Enemy;

FightingBehaviour::FightingBehaviour(Enemy* pEnemy)
	: m_pEnemy{pEnemy}
{
}
FightingBehaviour::~FightingBehaviour()
{
	m_pEnemy = nullptr;
}