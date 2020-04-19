#pragma once

class Enemy;

class DrawingBehaviour
{
public:
	DrawingBehaviour(Enemy* pEnemy);
	DrawingBehaviour(const DrawingBehaviour& other) = delete;
	DrawingBehaviour& operator=(const DrawingBehaviour& other) = delete;
	DrawingBehaviour(DrawingBehaviour&& other) = delete;
	DrawingBehaviour& operator=(DrawingBehaviour&& other) = delete;
	virtual ~DrawingBehaviour();

	virtual void Update(float elapsedSec) = 0;
	virtual void Draw() const = 0;

protected:
	Enemy* m_pEnemy;
};

