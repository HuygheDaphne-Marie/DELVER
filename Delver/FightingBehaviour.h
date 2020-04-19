#pragma once

class Enemy;

class FightingBehaviour
{
public:
	FightingBehaviour(Enemy* pEnemy);
	FightingBehaviour(const FightingBehaviour& other) = delete;
	FightingBehaviour& operator=(const FightingBehaviour& other) = delete;
	FightingBehaviour(FightingBehaviour&& other) = delete;
	FightingBehaviour& operator=(FightingBehaviour&& other) = delete;
	virtual ~FightingBehaviour();

	virtual void Update(float elapsedSec) = 0;
protected:
	Enemy* m_pEnemy;
};

