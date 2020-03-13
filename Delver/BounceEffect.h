#pragma once
#include "SpecialEffect.h"

static const int m_MaxBounces{ 1 };

class BounceEffect final : public SpecialEffect
{
public:
	BounceEffect();
	~BounceEffect();

	void ApplySpecialEffect(Bullet* bullet, const utils::HitInfo& hitInfo, float elapsedSec) override;

private:
	int m_BounceCount;
};

