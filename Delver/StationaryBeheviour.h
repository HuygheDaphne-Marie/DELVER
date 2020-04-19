#pragma once
#include "MovementBehaviour.h"

class StationaryBeheviour : public MovementBehaviour
{
public:
	StationaryBeheviour(Enemy* pEnemy);
	StationaryBeheviour(const StationaryBeheviour& other) = delete;
	StationaryBeheviour& operator=(const StationaryBeheviour& other) = delete;
	StationaryBeheviour(StationaryBeheviour&& other) = delete;
	StationaryBeheviour& operator=(StationaryBeheviour&& other) = delete;
	virtual ~StationaryBeheviour();

	virtual void Update(float elapsedSec) override;

private:
	const Point2f m_StartPos;
};

