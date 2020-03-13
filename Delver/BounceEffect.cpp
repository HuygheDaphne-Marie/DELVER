#include "pch.h"
#include "BounceEffect.h"
#include "Bullet.h"

BounceEffect::BounceEffect()
	: SpecialEffect(SpecialEffect::Type::bounce)
	, m_BounceCount{ 0 }
{
}
BounceEffect::~BounceEffect()
{
}

void BounceEffect::ApplySpecialEffect(Bullet* bullet, const utils::HitInfo& hitInfo, float elapsedSec)
{
	Vector2f reflect = bullet->GetVelocity().Reflect(hitInfo.normal);
	bullet->SetPosition(hitInfo.intersectPoint + (reflect * elapsedSec) * (1 - hitInfo.lambda));
	bullet->SetVelocity(reflect);

	m_BounceCount++;
	if (m_BounceCount > m_MaxBounces)
	{
		m_IsSpecialEffectDone = true;
	}
}