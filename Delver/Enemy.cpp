#include "pch.h"
#include "Enemy.h"
#include "Texture.h"

#include "StationaryBeheviour.h"
#include "PeacefulBehaviour.h"
#include "DrawingBehaviour.h"

#include "Gun.h"
#include "EnemyManager.h"

Enemy::Enemy(const ActorData& actorData, const BehaviourSet& behaviours, float detectionRange, int hitPoints, Gun* gun)
	: Actor(actorData)
	, m_DetectionRange{ detectionRange }
	, m_MaxHitPoints{ hitPoints }
	, m_CurrentHitpoints{ hitPoints }
	, m_pMovementBehavior{ behaviours.movementBehaviour }
	, m_pFightingBehaviour{ behaviours.fightingBehaviour }
	, m_pDrawingBehaviour{ behaviours.drawingBehaviour }
	, m_pEquippedGun{ gun }
	, m_State{ State::idle }
	, m_pTarget{ nullptr }
	, m_CanDelete{ false }
	, m_DeathHandled{ false }
{
	Initialize();
}
Enemy::~Enemy()
{
	if (m_pMovementBehavior != nullptr)
	{
		delete m_pMovementBehavior;
	}
	if (m_pFightingBehaviour != nullptr)
	{
		delete m_pFightingBehaviour;
	}
	if (m_pDrawingBehaviour != nullptr)
	{
		delete m_pDrawingBehaviour;
	}

	if (m_pEquippedGun != nullptr)
	{
		m_pEquippedGun->SetHolder(nullptr);
		delete m_pEquippedGun;
	}
}

void Enemy::Initialize()
{
	if (m_pMovementBehavior != nullptr)
	{
		m_pMovementBehavior->SetEnemy(this);
	}
	if (m_pFightingBehaviour != nullptr)
	{
		m_pFightingBehaviour->SetEnemy(this);
	}
	if (m_pDrawingBehaviour != nullptr)
	{
		m_pDrawingBehaviour->SetEnemy(this);
	}

	if (m_pEquippedGun != nullptr)
	{
		m_pEquippedGun->SetHolder(this);
		m_pEquippedGun->UpdateGunPos(m_Position);
	}
}

void Enemy::Update(float elapsedSec, const Level& level)
{
	if (m_pMovementBehavior != nullptr)
	{
		m_pMovementBehavior->Update(elapsedSec);
	}
	if (m_pFightingBehaviour != nullptr)
	{
		m_pFightingBehaviour->Update(elapsedSec);
	}
	if (m_pDrawingBehaviour != nullptr)
	{
		m_pDrawingBehaviour->Update(elapsedSec);
	}


	if (m_pEquippedGun != nullptr)
	{
		m_pEquippedGun->UpdateGun(elapsedSec);
	}

	Actor::Update(elapsedSec, level);

	if (IsDead())
	{
		HandleDeath();
	}

	if (m_CanDelete)
	{
		EnemyManager::GetInstance()->QueueToDestroy(this);
	}
}
void Enemy::Draw() const
{
	if (m_pDrawingBehaviour != nullptr)
	{
		m_pDrawingBehaviour->Draw();
	}
	else
	{
		Actor::Draw();
	}
}

bool Enemy::IsTargetInRange(const Actor& target) const
{
	return utils::GetDistanceSquared(m_Position, target.GetPosition()) < m_DetectionRange * m_DetectionRange;
}

bool Enemy::IsDead() const
{
	return m_CurrentHitpoints <= 0;
}
void Enemy::HandleDeath()
{
	if (m_DeathHandled)
	{
		return;
	}

	// TODO: make enemy animate a dead thiny with blood and stuff
	m_State = Enemy::State::dead;
	m_pEquippedGun->StopFiring();
	m_pEquippedGun->SetHolder(nullptr);

	if (m_CanDelete)
	{
		EnemyManager::GetInstance()->QueueToDestroy(this);
	}
	m_DeathHandled = true;
}

void Enemy::SetBehaviour(const Enemy::BehaviourSet& behaviour)
{
	if (behaviour.drawingBehaviour != nullptr)
	{
		SetDrawingBehaviour(behaviour.drawingBehaviour);
		m_pDrawingBehaviour->SetEnemy(this);
	}
	if (behaviour.movementBehaviour != nullptr)
	{
		SetMovementBehaviour(behaviour.movementBehaviour);
		m_pMovementBehavior->SetEnemy(this);
	}
	if (behaviour.fightingBehaviour != nullptr)
	{
		SetFightingBehaviour(behaviour.fightingBehaviour);
		m_pFightingBehaviour->SetEnemy(this);
	}
}
void Enemy::SetMovementBehaviour(MovementBehaviour* newBehaviour)
{
	if (m_pMovementBehavior != nullptr)
	{
		delete m_pMovementBehavior;
	}
	m_pMovementBehavior = newBehaviour;
}
void Enemy::SetFightingBehaviour(FightingBehaviour* newBehaviour)
{
	if (m_pFightingBehaviour != nullptr)
	{
		delete m_pFightingBehaviour;
	}
	m_pFightingBehaviour = newBehaviour;
}
void Enemy::SetDrawingBehaviour(DrawingBehaviour* newBehaviour)
{
	if (m_pDrawingBehaviour != nullptr)
	{
		delete m_pDrawingBehaviour;
	}
	m_pDrawingBehaviour = newBehaviour;
}

void Enemy::EquipGun(Gun* gun)
{
	if (m_pEquippedGun != nullptr)
	{
		delete m_pEquippedGun;
	}
	m_pEquippedGun = gun;
	m_pEquippedGun->SetHolder(this);
	m_pEquippedGun->UpdateGunPos(GetPosition());
}
Gun* Enemy::GetEquippedGun() const
{
	return m_pEquippedGun;
}