#pragma once
#include "Actor.h"
#include <vector>
#include "MovementBehaviour.h"
#include "FightingBehaviour.h"

class Gun;

class Enemy : public Actor
{
public:
	const int m_MaxHitPoints;
	int m_CurrentHitpoints;
	float m_DetectionRange;
	Gun* m_Gun;

	Enemy(const Point2f& pos, float detectionRange, int hitPoints);
	virtual ~Enemy();

	virtual void Update(float elapsedSec, const Level& level) override;
	virtual void Draw() const override;

	bool IsTargetInRange(const Actor& target) const;

	bool IsDead() const;
	void HandleDeath();

protected:
	MovementBehaviour& m_MovementBehavior;
	FightingBehaviour& m_FightingBehaviour;
};
