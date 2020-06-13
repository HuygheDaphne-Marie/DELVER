#include "pch.h"
#include "StationaryBeheviour.h"
#include "Enemy.h"

StationaryBeheviour::StationaryBeheviour()
	: StationaryBeheviour(nullptr)
{
}
StationaryBeheviour::StationaryBeheviour(Enemy* pEnemy)
	: MovementBehaviour(pEnemy)
	, m_StartPos{pEnemy->GetPosition()}
{
}
StationaryBeheviour::~StationaryBeheviour()
{
}

void StationaryBeheviour::Update(float elapsedSec)
{
	if (utils::GetDistanceSquared(m_StartPos, m_pEnemy->GetPosition()) > 1.f)
	{
		m_pEnemy->SetPosition(m_StartPos);
	}
}