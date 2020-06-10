#pragma once
#include "FightingBehaviour.h"
#include "Level.h"

class Actor;

class TurretBehaviour :	public FightingBehaviour
{
public:
	Actor* m_pTarget;
	static const float m_DeployDuration;

	TurretBehaviour(Actor* target, const Level& level);
	TurretBehaviour(Enemy* pEnemy, Actor* target, const Level& level);
	TurretBehaviour(const TurretBehaviour& other) = delete;
	TurretBehaviour& operator=(const TurretBehaviour& other) = delete;
	TurretBehaviour(TurretBehaviour&& other) = delete;
	TurretBehaviour& operator=(TurretBehaviour&& other) = delete;
	virtual ~TurretBehaviour();

	virtual void Update(float elapsedSec) override;
	virtual void Initialize() override;

protected:
	float m_Timer;
	
	const Level& m_Level;

	void Deploy(float elapsedSec);
	void Undeploy(float elapsedSec);
};

