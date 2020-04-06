#include "pch.h"
#include "Actor.h"
#include <vector>
#include "Texture.h"
#include "Room.h"
#include "Controller.h"

Actor::Actor(const Point2f& pos, Type type, Texture* texture, float collisionWidth, float collisionHeight, float acceleration, float frictionFactor)
	: m_Acceleration{ acceleration }
	, m_FrictionFactor{ frictionFactor }
	, m_Position{ pos }
	, m_Velocity{ 0, 0 }
	, m_Type{ type }
	, m_pTexture{ texture }
	, m_CollisionWidth{ collisionWidth }
	, m_CollisionHeight{ collisionHeight }
	, m_pController{ nullptr }
{
	if (m_CollisionWidth == -1 && m_CollisionHeight == -1) // Magic number but, negatives do not make any sense for dimensions anyway
	{
		if (m_pTexture != nullptr)
		{
			m_CollisionHeight = m_pTexture->GetHeight();
			m_CollisionWidth = m_pTexture->GetWidth();
		}
		else
		{
			m_CollisionHeight = 20.f;
			m_CollisionWidth = 20.f;
		}
	}
}
Actor::~Actor()
{
	m_pTexture = nullptr;
	if (m_pController != nullptr)
	{
		delete m_pController;
		m_pController = nullptr;
	}
}

void Actor::Update(float elapsedSec, const Level& level)
{
	Room* roomIAmIn{ level.GetRoomAt(m_Position) };
	if (roomIAmIn != nullptr)
	{
		HandleMovementCollision(roomIAmIn->GetBarriers(), elapsedSec);
	}
	m_Velocity *= m_FrictionFactor;
}
void Actor::Draw() const
{
	Rectf dstRect{ -m_CollisionWidth / 2, -m_CollisionHeight / 2, m_CollisionWidth, m_CollisionHeight };
	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, 0);
	{
		glColor3f(1.f, 1.f, 0.f);
		utils::FillRect(dstRect);
	}
	glPopMatrix();
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
float Actor::GetAcceleration() const
{
	return m_Acceleration;
}
Controller* Actor::GetController() const
{
	return m_pController;
}
void Actor::SetController(Controller* controller)
{
	if (m_pController != nullptr)
	{
		delete m_pController;
		m_pController = nullptr;
	}
	m_pController = controller;
}

void Actor::MoveUp(float elapsedSec)
{
	m_Velocity.y += m_Acceleration * elapsedSec;
}
void Actor::MoveDown(float elapsedSec)
{
	m_Velocity.y -= m_Acceleration * elapsedSec;
}
void Actor::MoveLeft(float elapsedSec)
{
	m_Velocity.x -= m_Acceleration * elapsedSec;
}
void Actor::MoveRight(float elapsedSec)
{
	m_Velocity.x += m_Acceleration * elapsedSec;
}

void Actor::HandleMovementCollision(const std::vector<std::vector<Point2f>>& vertecies, float elapsedSec)
{
	bool hasVerticalCollided{ false };
	bool hasHorizontalCollided{ false };

	for (const std::vector<Point2f>& vertex : vertecies)
	{
		utils::HitInfo hitInfo{};
		if (CheckVerticalCollision(vertex, hitInfo, elapsedSec))
		{
			m_Velocity.y = 0;
			hasVerticalCollided = true;
		}

		if (CheckHorizontalCollision(vertex, hitInfo, elapsedSec))
		{
			m_Velocity.x = 0;
			hasHorizontalCollided = true;
		}
	}

	if (!hasVerticalCollided)
	{
		m_Position.y += m_Velocity.y * elapsedSec;
	}
	if (!hasHorizontalCollided)
	{
		m_Position.x += m_Velocity.x * elapsedSec;
	}
}
bool Actor::CheckVerticalCollision(const std::vector<Point2f>& vertex, utils::HitInfo& hitInfo, float elapsedSec) const
{
	float heightAdjustment{ m_CollisionHeight / 2 };
	if (m_Velocity.y < -0.1f)
	{
		heightAdjustment *= -1;
	}

	const Point2f leftStart{ m_Position.x - m_CollisionWidth / 2, m_Position.y };
	const Point2f leftEnd{ leftStart.x, leftStart.y + (m_Velocity.y * elapsedSec) + heightAdjustment };
	if (utils::Raycast(vertex, leftStart, leftEnd, hitInfo))
	{
		return true;
	}

	const Point2f rightStart{ m_Position.x + m_CollisionWidth / 2, m_Position.y  };
	const Point2f rightEnd{ rightStart.x, rightStart.y + (m_Velocity.y * elapsedSec) + heightAdjustment };
	if (utils::Raycast(vertex, rightStart, rightEnd, hitInfo))
	{
		return true;
	}

	return false;
}
bool Actor::CheckHorizontalCollision(const std::vector<Point2f>& vertex, utils::HitInfo& hitInfo, float elapsedSec) const
{
	float widthAdjustment{ m_CollisionWidth / 2 };
	if (m_Velocity.x < -0.1f)
	{
		widthAdjustment *= -1;
	}

	const Point2f topStart{ m_Position.x, m_Position.y + m_CollisionHeight / 2 };
	const Point2f topEnd{ topStart.x + (m_Velocity.x * elapsedSec) + widthAdjustment, topStart.y };
	if (utils::Raycast(vertex, topStart, topEnd, hitInfo))
	{
		return true;
	}

	const Point2f bottomStart{ m_Position.x, m_Position.y - m_CollisionHeight / 2 };
	const Point2f bottomEnd{ bottomStart.x + (m_Velocity.x * elapsedSec) + widthAdjustment, bottomStart.y };
	if (utils::Raycast(vertex, bottomStart, bottomEnd, hitInfo))
	{
		return true;
	}

	return false;
}
