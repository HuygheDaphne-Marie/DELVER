#include "pch.h"
#include "TurretBehaviour.h"

#include "Level.h"
#include "Room.h"
#include "Enemy.h"
#include "Gun.h"

const float TurretBehaviour::m_DeployDuration = 0.5f;

TurretBehaviour::TurretBehaviour(Enemy* pEnemy, Actor* target, const Level& level)
	: FightingBehaviour(pEnemy)
	//, m_pTarget{target}
	, m_Timer{ 0.f }
	, m_Level{ level }
{
	pEnemy->m_pTarget = target;
}
TurretBehaviour::~TurretBehaviour()
{
	//if (m_pTarget != nullptr)
	//{
	//	m_pTarget = nullptr;
	//}
}

void TurretBehaviour::Update(float elapsedSec)
{
	if (m_pEnemy->IsDead())
	{
		return;
	}

	if (m_pEnemy->IsTargetInRange(*m_pEnemy->m_pTarget))
	{
		if (m_pEnemy->m_State != Enemy::State::fighting)
		{
			Deploy(elapsedSec);
		}

		if (m_pEnemy->m_State == Enemy::State::fighting)
		{
			if (m_pEnemy->GetEquippedGun() == nullptr)
			{
				return;
			}
			m_pEnemy->GetEquippedGun()->UpdateAimPos(m_pEnemy->m_pTarget->GetPosition());

			Room* room{ m_Level.GetRoomAt(m_pEnemy->GetPosition()) };
			if (room == nullptr)
			{
				return;
			}
			
			bool barrierInWay{ false };
			for (std::vector<Point2f> barrier : room->GetBarriers())
			{
				utils::HitInfo hitInfo{};
				if (utils::Raycast(barrier, m_pEnemy->GetPosition(), m_pEnemy->m_pTarget->GetPosition(), hitInfo))
				{
					barrierInWay = true;
				}
			}

			if (!barrierInWay)
			{
				m_pEnemy->GetEquippedGun()->StartFiring();
			}
			else
			{
				m_pEnemy->GetEquippedGun()->StopFiring();
			}
		}
	}
	else
	{
		if (m_pEnemy->m_State != Enemy::State::idle)
		{
			if (m_pEnemy->GetEquippedGun() != nullptr)
			{
				m_pEnemy->GetEquippedGun()->StopFiring();
			}
			Undeploy(elapsedSec);
		}
	}
}

void TurretBehaviour::Deploy(float elapsedSec)
{
	if (m_pEnemy->m_State != Enemy::State::deploying)
	{
		m_pEnemy->m_State = Enemy::State::deploying;
	}

	if (m_pEnemy->m_State == Enemy::State::deploying)
	{
		m_Timer += elapsedSec;
		if (m_Timer > m_DeployDuration)
		{
			m_pEnemy->m_State = Enemy::State::fighting;
			m_Timer = 0;
		}
	}
}
void TurretBehaviour::Undeploy(float elapsedSec)
{
	if (m_pEnemy->m_State != Enemy::State::undeploying)
	{
		m_pEnemy->m_State = Enemy::State::undeploying;
	}

	if (m_pEnemy->m_State == Enemy::State::undeploying)
	{
		m_Timer += elapsedSec;
		if (m_Timer > m_DeployDuration)
		{
			m_pEnemy->m_State = Enemy::State::idle;
			m_Timer = 0;
		}
	}
}
