#pragma once

class Enemy;

class DrawingBehaviour
{
public:
	DrawingBehaviour(Enemy* pEnemy);
	virtual ~DrawingBehaviour();

	virtual void Update(float elapsedSec) = 0;
	virtual void Draw() const = 0;

protected:
	Enemy* m_pEnemy;
};

