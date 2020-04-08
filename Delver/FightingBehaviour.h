#pragma once
class FightingBehaviour
{
public:
	FightingBehaviour(Enemy* pEnemy);
	virtual ~FightingBehaviour();

	virtual void Update(float elapsedSec) = 0;

protected:
	Enemy* m_pEnemy;
};

