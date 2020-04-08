#pragma once
#include "FightingBehaviour.h"
#include "Level.h"

class Actor;

class TurretBehaviour :	public FightingBehaviour
{
public:
	Actor* m_pTarget;

	TurretBehaviour(Enemy* pEnemy, Actor* target, const Level& level);
	virtual ~TurretBehaviour();

	virtual void Update(float elapsedSec) override;

protected:
	float m_Timer;
	static const float m_DeployDuration;
	const Level& m_Level;

	void Deploy(float elapsedSec);
	void Undeploy(float elapsedSec);
};

