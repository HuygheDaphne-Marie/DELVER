#pragma once
#include "Player.h"

class Item
{
public:
	enum class ItemType
	{
		pickup
	};

	const ItemType m_ItemType;
	Point2f m_SpawnPos;
	float m_Width, m_Height;
	Point2f m_Posistion;
	Vector2f m_Velocity;
	bool m_PickedUp;

	Item(const ItemType& itemType, const Point2f& pos, const Vector2f& velocity = Vector2f{ 0,0 }, float width = 30.f, float height = 30.f);
	virtual ~Item();

	virtual void Update(float elapsedSec, Player& player);
	virtual void Draw() const = 0;
	virtual void OnPickup(Player& player);
	bool CheckPickup(const Rectf& box);
};

