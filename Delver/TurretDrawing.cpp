#include "pch.h"
#include "TurretDrawing.h"
#include "TurretBehaviour.h"
#include "Enemy.h"
#include "Vector2f.h"
#include <iterator>

TurretDrawing::TurretDrawing(Enemy* pEnemy)
	: DrawingBehaviour(pEnemy)
	, m_SrcPath{ "Resources/Textures/Actors/Turret.png" }
	, m_Animations{}
	, m_LastState{ pEnemy->m_State }
	, m_CurrentAnimation{ nullptr }
{
	m_Animations[Enemy::State::idle] = new Animation(m_SrcPath, Point2f{ 0, 124 }, 124, 124, 3, 0.5f);
	m_Animations[Enemy::State::deploying] = new Animation(m_SrcPath, Point2f{ 0, 248 }, 124, 124, 5, TurretBehaviour::m_DeployDuration / 5, false);
	m_Animations[Enemy::State::fighting] = new Animation(m_SrcPath, Point2f{ 0, 372 }, 124, 124, 8, 2.f/8);
	m_Animations[Enemy::State::undeploying] = new Animation(m_SrcPath, Point2f{ 496, 248 }, 124, 124, 5, TurretBehaviour::m_DeployDuration / 5, false, true);
	
	m_CurrentAnimation = GetAnimation(pEnemy->m_State);
}
TurretDrawing::~TurretDrawing()
{
	for (std::map<Enemy::State, Animation*>::iterator itr{m_Animations.begin()}; itr != m_Animations.end(); itr++)
	{
		delete (*itr).second;
		(*itr).second = nullptr;
	}
}

void TurretDrawing::Update(float elapsedSec)
{
	if (m_pEnemy->m_State != m_LastState)
	{
		if (m_pEnemy->m_State == Enemy::State::deploying && m_LastState == Enemy::State::undeploying || 
			m_pEnemy->m_State == Enemy::State::undeploying && m_LastState == Enemy::State::deploying)
		{
			int startFrame = m_CurrentAnimation->GetCurrentFrame();
			m_CurrentAnimation->ResetAnimation();
		
			m_CurrentAnimation = GetAnimation(m_pEnemy->m_State);
			m_CurrentAnimation->SetCurrentFrame(startFrame);
			m_LastState = m_pEnemy->m_State;
			return;
		}

		if (m_CurrentAnimation != nullptr)
		{
			m_CurrentAnimation->ResetAnimation();
		}
		m_CurrentAnimation = GetAnimation(m_pEnemy->m_State);
		m_LastState = m_pEnemy->m_State;
	}

	if (m_CurrentAnimation != nullptr && m_LastState != Enemy::State::fighting)
	{
		m_CurrentAnimation->Update(elapsedSec);
	}
	if (m_CurrentAnimation != nullptr && m_LastState == Enemy::State::fighting)
	{
		SetRightTurretRotationTexture();
	}
}
void TurretDrawing::Draw() const
{
	if (m_CurrentAnimation == nullptr)
	{
		return;
	}

	Point2f pos{ m_pEnemy->GetPosition() };
	pos.x -= m_pEnemy->m_Width / 2;
	pos.y -= m_pEnemy->m_Height / 2;
	m_CurrentAnimation->Draw(Rectf{ pos.x, pos.y, m_pEnemy->m_Width, m_pEnemy->m_Height });
}

Animation* TurretDrawing::GetAnimation(Enemy::State state) const
{
	std::map<Enemy::State, Animation*>::const_iterator result = m_Animations.find(state);
	if (result != m_Animations.end())
	{
		return (*result).second;
	}
	return nullptr;
}

void TurretDrawing::SetRightTurretRotationTexture()
{
	const int textureAngleStep{ 45 };
	const Vector2f downwards{ 0, -1 };
	const Vector2f toTarget{ m_pEnemy->GetPosition(), m_pEnemy->m_pTarget->GetPosition() };
	const float radians{ toTarget.AngleWith(downwards) };

	float degrees{ float(radians * (180.f / M_PI)) };
	degrees += textureAngleStep / 2.f; // gives some slack to the angle, follows better this way.

	if (degrees < 0)
	{
		degrees = 180.f + (180.f + degrees);
	}

	const int rightFrame{ int(degrees / textureAngleStep) };
	if (rightFrame != m_CurrentAnimation->GetCurrentFrame())
	{
		m_CurrentAnimation->SetCurrentFrame(rightFrame);
	}
}