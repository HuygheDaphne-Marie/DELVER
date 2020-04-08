#include "pch.h"
#include "PeacefulBehaviour.h"

PeacefulBehaviour::PeacefulBehaviour(Enemy* pEnemy)
	: FightingBehaviour(pEnemy)
{
}
PeacefulBehaviour::~PeacefulBehaviour()
{
}

void PeacefulBehaviour::Update(float elapsedSec)
{
	// Yeah literally does nothing...
}