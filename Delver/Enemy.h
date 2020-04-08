#pragma once
#include "Actor.h"
#include <vector>
#include "MovementBehaviour.h"
#include "FightingBehaviour.h"

class Gun;

class Enemy : public Actor
{
public:
	enum class State
	{
		idle,
		deploying,
		fighting,
		undeploying
	};

	State m_State;
	const int m_MaxHitPoints;
	int m_CurrentHitpoints;
	float m_DetectionRange;

	Enemy(const Point2f& pos, float detectionRange, int hitPoints, Gun* gun = nullptr,  MovementBehaviour* movementBehaviour = nullptr, FightingBehaviour* fightingBehaviour = nullptr);
	virtual ~Enemy();

	virtual void Update(float elapsedSec, const Level& level);
	virtual void Draw() const override;

	bool IsTargetInRange(const Actor& target) const;

	bool IsDead() const;
	void HandleDeath();

	void SetMovementBehaviour(MovementBehaviour* newBehaviour);
	void SetFightingBehaviour(FightingBehaviour* newBehaviour);

	void EquipGun(Gun* gun);
	Gun* GetEquippedGun() const;

protected:
	Gun* m_pEquippedGun;
	MovementBehaviour* m_pMovementBehavior;
	FightingBehaviour* m_pFightingBehaviour;
};
