#include "pch.h"
#include "Actor.h"
#include <vector>
#include "Texture.h"
#include "Room.h"
#include "Controller.h"

Actor::Actor(const ActorData& data, float acceleration, float frictionFactor)
	: m_Acceleration{ acceleration }
	, m_FrictionFactor{ frictionFactor }
	, m_Velocity{ 0, 0 }
	, m_Position{ data.pos }
	, m_Type{ data.type }
	, m_pTexture{ data.pTexture }
	, m_Width{ data.dimension.width }
	, m_Height{ data.dimension.height }
	, m_CollisionRect{ data.dimension.collisionBox }
{
}
Actor::~Actor()
{
	m_pTexture = nullptr;
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
	const Rectf dstRect{ -m_Width / 2, -m_Height / 2, m_Width, m_Height };
	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, 0);
	{
		if (m_Type == Type::player)
		{
			glColor3f(1.f, 1.f, 0.f);
		}
		else
		{
			glColor3f(1.f, 0.f, 0.f);
		}
		
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

bool Actor::isPointInCollisionRect(const Point2f& pos) const
{
	const Point2f leftBottom{ m_Position.x - m_Width / 2, m_Position.y - m_Height / 2 };
	Rectf collisonRect{ leftBottom.x + m_CollisionRect.left, leftBottom.y + m_CollisionRect.bottom, m_CollisionRect.width, m_CollisionRect.height };
	return utils::IsPointInRect(pos, collisonRect);
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
	const Point2f checkOriginPos{ m_Position.x - m_Width / 2, m_Position.y };
	float heightAdjustment{ m_Height / 2 };
	if (m_Velocity.y < -0.1f)
	{
		heightAdjustment *= -1;
	}

	Point2f leftStart{ checkOriginPos.x + m_CollisionRect.left, checkOriginPos.y + m_CollisionRect.bottom };
	Point2f leftEnd{ leftStart.x, leftStart.y + (m_Velocity.y * elapsedSec) + heightAdjustment };
	while (leftStart.x < checkOriginPos.x + m_CollisionRect.left + m_CollisionRect.width)
	{
		if (utils::Raycast(vertex, leftStart, leftEnd, hitInfo))
		{
			return true;
		}
		leftStart.x += Tile::m_Side;
		leftEnd.x += Tile::m_Side;
	}

	// Making sure we check the last bit, since while might miss it
	const Point2f rightStart{ checkOriginPos.x + m_CollisionRect.left + m_CollisionRect.width, checkOriginPos.y + m_CollisionRect.bottom };
	const Point2f rightEnd{ rightStart.x, rightStart.y + (m_Velocity.y * elapsedSec) + heightAdjustment };
	if (utils::Raycast(vertex, rightStart, rightEnd, hitInfo))
	{
		return true;
	}

	return false;
}
bool Actor::CheckHorizontalCollision(const std::vector<Point2f>& vertex, utils::HitInfo& hitInfo, float elapsedSec) const
{
	const Point2f checkOriginPos{ m_Position.x, m_Position.y - m_Height / 2 };
	float widthAdjustment{ m_Width / 2 };
	if (m_Velocity.x < -0.1f)
	{
		widthAdjustment *= -1;
	}

	Point2f topStart{ checkOriginPos.x + m_CollisionRect.left, checkOriginPos.y + m_CollisionRect.bottom + m_CollisionRect.height };
	Point2f topEnd{ topStart.x + (m_Velocity.x * elapsedSec) + widthAdjustment, topStart.y };
	while (topStart.y > checkOriginPos.y + m_CollisionRect.bottom)
	{
		if (utils::Raycast(vertex, topStart, topEnd, hitInfo))
		{
			return true;
		}
		topStart.y -= Tile::m_Side;
		topEnd.y -= Tile::m_Side;
	}

	// Making sure we check the last bit, since while might miss it
	const Point2f bottomStart{ checkOriginPos.x + m_CollisionRect.left, checkOriginPos.y + m_CollisionRect.bottom };
	const Point2f bottomEnd{ bottomStart.x + (m_Velocity.x * elapsedSec) + widthAdjustment, bottomStart.y };
	if (utils::Raycast(vertex, bottomStart, bottomEnd, hitInfo))
	{
		return true;
	}

	return false;
}
