#pragma once
#include "MovementBehaviour.h"

class StationaryBeheviour : public MovementBehaviour
{
public:
	StationaryBeheviour(Enemy* pEnemy);
	virtual ~StationaryBeheviour();

	virtual void Update(float elapsedSec) override;

private:
	const Point2f m_StartPos;
};

