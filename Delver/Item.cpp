#include "pch.h"
#include "Item.h"

Item::Item(const ItemType& itemType, const Point2f& pos, const Vector2f& velocity, float width, float height)
	: m_ItemType{ itemType }
	, m_SpawnPos{ pos }
	, m_Posistion{ pos }
	, m_Velocity{ velocity }
	, m_Width{ width }
	, m_Height{ height }
	, m_PickedUp{ false }
{
}
Item::~Item()
{
}

void Item::Update(float elapsedSec)
{
	m_Posistion += m_Velocity * elapsedSec;
	m_Velocity *= 0.9f;
}

void Item::OnPickup(Player& player)
{
	m_PickedUp = true;
}