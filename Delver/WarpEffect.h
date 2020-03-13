#pragma once
#include "SpecialEffect.h"

static const int m_MaxWarps{ 1 };

class WarpEffect final : public SpecialEffect
{
public:
	WarpEffect();
	~WarpEffect();

	void ApplySpecialEffect(Bullet* bullet, const utils::HitInfo& hitInfo, float elapsedSec) override;

private:
	int m_WarpCount;
};

