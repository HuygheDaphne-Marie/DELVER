#pragma once

class Enemy;

class MovementBehaviour
{
public: 
	MovementBehaviour(Enemy* pEnemy);
	virtual ~MovementBehaviour();

	virtual void Update(float elapsedSec) = 0;

protected:
	Enemy* m_pEnemy;
};

