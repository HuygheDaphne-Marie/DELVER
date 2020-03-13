#include "pch.h"
#include "Actor.h"

#include "Texture.h"

Actor::Actor(const Point2f& pos, Type type, Texture* texture, float speed)
	: m_Speed{ speed }
	, m_Position{ pos }
	, m_Velocity{ 0, 0 }
	, m_Type{ type }
	, m_pTexture{ texture }
{
}
Actor::~Actor()
{
	m_pTexture = nullptr;
}

void Actor::Update(float elapsedSec)
{
	m_Position += m_Velocity * elapsedSec;
}
void Actor::Draw() const
{
	const float width{ 20.f }, height{ 20.f };
	glColor3f(1.f, 1.f, 0.f);
	utils::FillRect(Rectf{ m_Position.x - width / 2, m_Position.y - height / 2, width, height });
}

Point2f Actor::GetPosition() const
{
	return m_Position;
}
void Actor::SetPosition(const Point2f& pos)
{
	m_Position = pos;
}
Vector2f Actor::GetVelocity() const
{
	return m_Velocity;
}
void Actor::SetVelocity(const Vector2f& velocity)
{
	m_Velocity = velocity;
}