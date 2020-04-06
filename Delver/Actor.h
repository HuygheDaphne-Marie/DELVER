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

	Actor(const Point2f& pos, Type type = Type::enemy, Texture* texture = nullptr, float collisionWidth = -1, float collisionHeight = -1, float acceleration = 2000.f, float frictionFactor = 0.9f);
	virtual ~Actor();

	virtual void Update(float elapsedSec, const Level& level);
	virtual void Draw() const;

	Point2f GetPosition() const;
	void SetPosition(const Point2f& pos);
	Vector2f GetVelocity() const;
	void SetVelocity(const Vector2f& velocity);
	float GetAcceleration() const;
	Controller* GetController() const;
	void SetController(Controller* controller);

	void MoveUp(float elapsedSec);
	void MoveDown(float elapsedSec);
	void MoveLeft(float elapsedSec);
	void MoveRight(float elapsedSec);

protected:
	float m_Acceleration;
	float m_FrictionFactor;
	Point2f m_Position;
	Vector2f m_Velocity;
	Type m_Type;
	Texture* m_pTexture;
	float m_Width;
	float m_Height;

	Controller* m_pController;

	void HandleMovementCollision(const std::vector<std::vector<Point2f>>& vertecies, float elapsedSec);
	bool CheckVerticalCollision(const std::vector<Point2f>& vertex, utils::HitInfo& hitInfo, float elapsedSec) const;
	bool CheckHorizontalCollision(const std::vector<Point2f>& vertex, utils::HitInfo& hitInfo, float elapsedSec) const;
};

