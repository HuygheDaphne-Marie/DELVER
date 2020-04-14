#pragma once
#include "Vector2f.h"
#include "Level.h"
class Texture;
class Controller;

class Actor
{
public:
	enum class Type
	{
		enemy,
		player
	};

	struct Dimension
	{
		Dimension(float w, float h, Rectf cb)
			: width{ w }
			, height{ h }
			, collisionBox{ cb }
		{
		}
		Dimension(float w, float h)
			: Dimension(w, h, Rectf{ 0, 0, w, h })
		{
		}

		float width;
		float height;
		Rectf collisionBox; // relative to bottom left of texture
	};

	struct ActorData
	{
		Point2f pos;
		Dimension dimension;
		Type type = Type::enemy;
		Texture* pTexture = nullptr;
	};

	const Type m_Type;
	float m_Width;
	float m_Height;

	Actor(const ActorData& data, float acceleration = 2000.f, float frictionFactor = 0.9f);

	Actor(const Point2f& pos, Type type = Type::enemy, Texture* texture = nullptr, float width = -1, float height = -1, float acceleration = 2000.f, float frictionFactor = 0.9f);
	virtual ~Actor();

	virtual void Update(float elapsedSec, const Level& level);
	virtual void Draw() const;

	Point2f GetPosition() const;
	void SetPosition(const Point2f& pos);
	Vector2f GetVelocity() const;
	void SetVelocity(const Vector2f& velocity);
	float GetAcceleration() const;

	void MoveUp(float elapsedSec);
	void MoveDown(float elapsedSec);
	void MoveLeft(float elapsedSec);
	void MoveRight(float elapsedSec);

protected:
	float m_Acceleration;
	float m_FrictionFactor;
	Point2f m_Position;
	Vector2f m_Velocity;
	Texture* m_pTexture;

	void HandleMovementCollision(const std::vector<std::vector<Point2f>>& vertecies, float elapsedSec);
	bool CheckVerticalCollision(const std::vector<Point2f>& vertex, utils::HitInfo& hitInfo, float elapsedSec) const;
	bool CheckHorizontalCollision(const std::vector<Point2f>& vertex, utils::HitInfo& hitInfo, float elapsedSec) const;
};

