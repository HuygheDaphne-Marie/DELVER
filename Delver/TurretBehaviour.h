#pragma once
#include "FightingBehaviour.h"
#include "Level.h"

class Actor;

class TurretBehaviour :	public FightingBehaviour
{
public:
	//Actor* m_pTarget;
	static const float m_DeployDuration;

	TurretBehaviour(Enemy* pEnemy, Actor* target, const Level& level);
	virtual ~TurretBehaviour();

	virtual void Update(float elapsedSec) override;

protected:
	float m_Timer;
	
	const Level& m_Level;

	void Deploy(float elapsedSec);
	void Undeploy(float elapsedSec);
};

