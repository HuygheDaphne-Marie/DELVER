#pragma once

class Enemy;

class MovementBehaviour
{
public: 
	MovementBehaviour(Enemy* pEnemy);
	MovementBehaviour(const MovementBehaviour& other) = delete;
	MovementBehaviour& operator=(const MovementBehaviour& other) = delete;
	MovementBehaviour(MovementBehaviour&& other) = delete;
	MovementBehaviour& operator=(MovementBehaviour&& other) = delete;
	virtual ~MovementBehaviour();

	virtual void Update(float elapsedSec) = 0;
	virtual void Initialize();

	void SetEnemy(Enemy* enemy);

protected:
	Enemy* m_pEnemy;
};

