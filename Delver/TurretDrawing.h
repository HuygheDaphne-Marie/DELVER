#pragma once
#include "DrawingBehaviour.h"
#include "Animation.h"
#include "AnimatedTexture.h"
#include "Enemy.h"
#include <map>

class TurretDrawing : public DrawingBehaviour
{
public:
	TurretDrawing();
	TurretDrawing(Enemy* pEnemy);
	TurretDrawing(const TurretDrawing& other) = delete;
	TurretDrawing& operator=(const TurretDrawing& other) = delete;
	TurretDrawing(TurretDrawing&& other) = delete;
	TurretDrawing& operator=(TurretDrawing&& other) = delete;
	virtual ~TurretDrawing();

	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;
	virtual void Initialize() override;

protected:
	std::map<Enemy::State, Animation*> m_Animations;
	Enemy::State m_LastState;
	const std::string m_SrcPath;
	AnimatedTexture m_DeathExplosion;
	bool m_IsDead;

	Animation* m_pCurrentAnimation;

	Animation* GetAnimation(Enemy::State state) const;

	void SetRightTurretRotationTexture();
};

