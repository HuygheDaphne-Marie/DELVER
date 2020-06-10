#include "pch.h"
#include "PeacefulBehaviour.h"

#include "Enemy.h"

PeacefulBehaviour::PeacefulBehaviour()
	: PeacefulBehaviour(nullptr)
{
}
PeacefulBehaviour::PeacefulBehaviour(Enemy* pEnemy)
	: FightingBehaviour{pEnemy}
{
}
PeacefulBehaviour::~PeacefulBehaviour()
{
}

void PeacefulBehaviour::Update(float elapsedSec)
{
	// Yeah literally does nothing... could technically be deleted now that this does the same as a nullptr, 
	// but might be nice to have an actual representation of "doing nothing" other than nullptr
	// will sleep on it, not really critical issue
}