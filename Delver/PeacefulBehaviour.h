#pragma once
#include "FightingBehaviour.h"

class Enemy;

class PeacefulBehaviour : public FightingBehaviour
{
public:
	PeacefulBehaviour(Enemy* pEnemy);
	virtual ~PeacefulBehaviour();

	virtual void Update(float elapsedSec) override;

private:
};

