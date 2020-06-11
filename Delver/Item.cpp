#include "pch.h"
#include "Item.h"

Item::Item(const ItemType& itemType, const Point2f& pos, float width, float height, const Vector2f& velocity)
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
}

void Item::OnPickup(Player& player)
{
	m_PickedUp = true;
}