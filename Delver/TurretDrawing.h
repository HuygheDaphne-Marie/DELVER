#pragma once
#include "DrawingBehaviour.h"
#include "Animation.h"
#include "Enemy.h"
#include <map>

class TurretDrawing : public DrawingBehaviour
{
public:
	TurretDrawing(Enemy* pEnemy);
	virtual ~TurretDrawing();

	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;

protected:
	std::map<Enemy::State, Animation*> m_Animations;
	Enemy::State m_LastState;
	const std::string m_SrcPath;

	Animation* m_CurrentAnimation;

	Animation* GetAnimation(Enemy::State state) const;

	void SetRightTurretRotationTexture();
};
