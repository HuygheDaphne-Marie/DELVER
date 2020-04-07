#pragma once
#include "Actor.h"
#include <vector>

class Gun;

class Enemy : public Actor
{
public:
	Enemy(const Point2f& pos, float detectionRange, int hitPoints);
	virtual ~Enemy();

	virtual void Update(float elapsedSec, const Level& level) override;
	virtual void Draw() const override;

	bool IsATargetInRange(const Actor& target) const;

private:
	float m_DetectionRange;
	int m_CurrentHitpoints;
	const int m_MaxHitPoints;
};

