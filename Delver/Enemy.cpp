#include "pch.h"
#include "Enemy.h"
#include "Texture.h"

Enemy::Enemy(const Point2f& pos, float detectionRange, int hitPoints)
	: Actor(pos, Actor::Type::enemy)
	, m_DetectionRange{}
	, m_MaxHitPoints{}
	, m_CurrentHitpoints{}
{
}
Enemy::~Enemy()
{

}

void Enemy::Update(float elapsedSec, const Level& level)
{
	m_MovementBehavior.Update(elapsedSec);
	m_FightingBehaviour.Update(elapsedSec);

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