#pragma once
#include "FightingBehaviour.h"

class Enemy;

class PeacefulBehaviour : public FightingBehaviour
{
public:
	PeacefulBehaviour();
	PeacefulBehaviour(Enemy* pEnemy);
	PeacefulBehaviour(const PeacefulBehaviour& other) = delete;
	PeacefulBehaviour& operator=(const PeacefulBehaviour& other) = delete;
	PeacefulBehaviour(PeacefulBehaviour&& other) = delete;
	PeacefulBehaviour& operator=(PeacefulBehaviour&& other) = delete;
	virtual ~PeacefulBehaviour();

	virtual void Update(float elapsedSec) override;

protected:
};

