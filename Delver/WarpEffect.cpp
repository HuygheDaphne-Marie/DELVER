#include "pch.h"
#include "WarpEffect.h"
#include "Bullet.h"


WarpEffect::WarpEffect()
	: SpecialEffect(SpecialEffect::Type::warp)
	, m_WarpCount{ 0 }
{
}
WarpEffect::~WarpEffect()
{
}

void WarpEffect::ApplySpecialEffect(Bullet* bullet, const utils::HitInfo& hitInfo, float elapsedSec)
{
	Vector2f inverted{ bullet->GetVelocity() * -1 };
	bullet->SetPosition(bullet->GetPosition() + inverted); // going into opposite direction for distance traveled in 1 sec

	m_WarpCount++;
	if (m_WarpCount > m_MaxWarps)
	{
		m_IsSpecialEffectDone = true;
	}
}
