#pragma once
#include "Vector2f.h"
#include "Level.h"
class Texture;

class Actor
{
public:
	enum class Type
	{
		enemy,
		player
	};

	Actor(const Point2f& pos, Type type = Type::enemy, Texture* texture = nullptr, float speed = 40.f, float frictionFactor = 0.9f);
	virtual ~Actor();

	virtual void Update(float elapsedSec, const Level& level);
	virtual void Draw() const;

	Point2f GetPosition() const;
	void SetPosition(const Point2f& pos);
	Vector2f GetVelocity() const;
	void SetVelocity(const Vector2f& velocity);

protected:
	float m_Speed;
	float m_FrictionFactor;
	Point2f m_Position;
	Vector2f m_Velocity;
	Type m_Type;
	Texture* m_pTexture;
	float m_Width;
	float m_Height;

	void HandleMovementCollision(const std::vector<std::vector<Point2f>>& vertecies);
	bool CheckVerticalCollision(const std::vector<Point2f>& vertex, utils::HitInfo& hitInfo) const;
	bool CheckHorizontalCollision(const std::vector<Point2f>& vertex, utils::HitInfo& hitInfo) const;
};

