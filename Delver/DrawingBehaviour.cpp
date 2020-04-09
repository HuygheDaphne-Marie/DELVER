#include "pch.h"
#include "DrawingBehaviour.h"

#include "Enemy.h"

DrawingBehaviour::DrawingBehaviour(Enemy* pEnemy)
	: m_pEnemy{pEnemy}
{
}
DrawingBehaviour::~DrawingBehaviour()
{
	m_pEnemy = nullptr;
}