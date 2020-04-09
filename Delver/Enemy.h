#pragma once
#include "Actor.h"
#include <vector>
#include "MovementBehaviour.h"
#include "FightingBehaviour.h"
#include "DrawingBehaviour.h"

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
	Actor* m_pTarget;

	Enemy(const Point2f& pos, float detectionRange, int hitPoints, Gun* gun = nullptr,  MovementBehaviour* movementBehaviour = nullptr, FightingBehaviour* fightingBehaviour = nullptr, DrawingBehaviour* = nullptr);
	virtual ~Enemy();

	virtual void Update(float elapsedSec, const Level& level);
	virtual void Draw() const override;

	bool IsTargetInRange(const Actor& target) const;

	bool IsDead() const;
	void HandleDeath();

	void SetMovementBehaviour(MovementBehaviour* newBehaviour);
	void SetFightingBehaviour(FightingBehaviour* newBehaviour);
	void SetDrawingBehaviour(DrawingBehaviour* newBehaviour);

	void EquipGun(Gun* gun);
	Gun* GetEquippedGun() const;

protected:
	Gun* m_pEquippedGun;
	MovementBehaviour* m_pMovementBehavior;
	FightingBehaviour* m_pFightingBehaviour;
	DrawingBehaviour* m_pDrawingBehaviour;
};
