#include "pch.h"
#include "Enemy.h"
#include "Texture.h"

#include "StationaryBeheviour.h"
#include "PeacefulBehaviour.h"

#include "Gun.h"

Enemy::Enemy(const Point2f& pos, float detectionRange, int hitPoints, Gun* gun, MovementBehaviour* movementBehaviour, FightingBehaviour* fightingBehaviour)
	: Actor(pos, Actor::Type::enemy)
	, m_DetectionRange{ detectionRange }
	, m_MaxHitPoints{ hitPoints }
	, m_CurrentHitpoints{ hitPoints }
	, m_pMovementBehavior{ movementBehaviour }
	, m_pFightingBehaviour{ fightingBehaviour }
	, m_pEquippedGun{ gun }
	, m_State{ State::idle }
{
	if (m_pEquippedGun != nullptr)
	{
		m_pEquippedGun->SetHolder(this);
		m_pEquippedGun->UpdateGunPos(pos);
	}
}
Enemy::~Enemy()
{
	if (m_pMovementBehavior != nullptr)
	{
		delete m_pMovementBehavior;
		m_pMovementBehavior = nullptr;
	}
	if (m_pFightingBehaviour != nullptr)
	{
		delete m_pFightingBehaviour;
		m_pFightingBehaviour = nullptr;
	}

	if (m_pEquippedGun != nullptr)
	{
		delete m_pEquippedGun;
		m_pEquippedGun = nullptr;
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

	if (m_pEquippedGun != nullptr)
	{
		m_pEquippedGun->UpdateGun(elapsedSec);
	}

	Actor::Update(elapsedSec, level);
}
void Enemy::Draw() const
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Draw(Point2f{ m_Position.x - m_pTexture->GetWidth() / 2, m_Position.y - m_pTexture->GetHeight() / 2 });
	}
	else
	{
		Actor::Draw();
	}
}

bool Enemy::IsTargetInRange(const Actor& target) const
{
	return utils::GetDistance(m_Position, target.GetPosition()) < m_DetectionRange;
}

bool Enemy::IsDead() const
{
	return m_CurrentHitpoints <= 0;
}
void Enemy::HandleDeath()
{
	// TODO
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

void Enemy::EquipGun(Gun* gun)
{
	if (m_pEquippedGun != nullptr)
	{
		delete m_pEquippedGun;
	}
	m_pEquippedGun = gun;
	m_pEquippedGun->UpdateGunPos(GetPosition());
}
Gun* Enemy::GetEquippedGun() const
{
	return m_pEquippedGun;
}