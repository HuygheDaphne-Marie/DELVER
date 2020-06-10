#include "pch.h"
#include "DrawingBehaviour.h"

#include "Enemy.h"

DrawingBehaviour::DrawingBehaviour(Enemy* pEnemy)
	: m_pEnemy{pEnemy}
{
	if (m_pEnemy != nullptr)
	{
		Initialize();
	}
}
DrawingBehaviour::~DrawingBehaviour()
{
	m_pEnemy = nullptr;
}
void DrawingBehaviour::Initialize()
{
}

void DrawingBehaviour::SetEnemy(Enemy* enemy)
{
	if (enemy != nullptr && m_pEnemy == nullptr)
	{
		m_pEnemy = enemy;
		Initialize();
	}
}
