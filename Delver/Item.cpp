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

void Item::Update(float elapsedSec, Player& player)
{
	if (m_PickedUp)
	{
		return;
	}

	m_Posistion += m_Velocity * elapsedSec;
	m_Velocity *= 0.9f;

	const Rectf playerRect{ player.GetPosition().x - m_Width / 2, player.GetPosition().y - m_Height / 2, player.m_Width, player.m_Height };
	if (CheckPickup(playerRect))
	{
		OnPickup(player);
	}
}

void Item::OnPickup(Player& player)
{
	m_PickedUp = true;
}

bool Item::CheckPickup(const Rectf& box)
{
	return utils::IsOverlapping(box, Rectf{ m_Posistion.x - m_Width / 2, m_Posistion.y - m_Height / 2, m_Width, m_Height });
}