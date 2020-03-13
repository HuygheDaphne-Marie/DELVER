#pragma once
#include "Vector2f.h"
class Texture;

class Actor
{
public:
	enum class Type
	{
		enemy,
		player
	};

	Actor(const Point2f& pos, Type type = Type::enemy, Texture* texture = nullptr, float speed = 100.f);
	virtual ~Actor();

	virtual void Update(float elapsedSec);
	virtual void Draw() const;

	Point2f GetPosition() const;
	void SetPosition(const Point2f& pos);
	Vector2f GetVelocity() const;
	void SetVelocity(const Vector2f& velocity);

protected:
	float m_Speed;
	Point2f m_Position;
	Vector2f m_Velocity;
	Type m_Type;
	Texture* m_pTexture;
};

