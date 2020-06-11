#include "pch.h"
#include "Pickup.h"

#include "TextureManager.h"
#include <sstream>


Pickup::Pickup(const PickupType& type, float effectDuration, const Point2f& pos, const Vector2f& velocity)
	: Item(ItemType::pickup, pos, 10.f, 10.f, velocity)
	, m_Type{ type }
	, m_EffectDuration{ effectDuration }
	, m_EffectTimer{ 0 }
	, m_pAffectPlayer{ nullptr }
	, m_pTexture{ nullptr }
{
	switch (type)
	{
	case PickupType::bounce:
		m_pTexture = TextureManager::GetInstance()->GetTexture("bounce_pickup_texture");
		break;
	case PickupType::warp: 
		m_pTexture = TextureManager::GetInstance()->GetTexture("warp_pickup_texture");
		break;
	}

	if (m_pTexture != nullptr)
	{
		m_Width = m_pTexture->GetWidth();
		m_Height = m_pTexture->GetHeight();
	}
}
Pickup::Pickup(const std::string& stringData)
	: Item(ItemType::pickup, Point2f{0,0}, 0.f, 0.f)
	, m_Type{ PickupType::bounce }
	, m_EffectDuration{ 0 }
	, m_EffectTimer{ 0 }
	, m_pAffectPlayer{ nullptr }
	, m_pTexture{ nullptr }
{
	std::string type{ utils::GetAttributeValue("Type", stringData) };
	if (type == "bounce")
	{
		m_Type = PickupType::bounce;
	}
	else if (type == "warp")
	{
		m_Type = PickupType::warp;
	}

	std::string effectDuration{ utils::GetAttributeValue("EffectDuration", stringData) };
	std::stringstream ss{};
	ss << effectDuration;
	ss >> m_EffectDuration;

	m_Posistion = utils::ToPoint2f(utils::GetAttributeValue("Posistion", stringData));
	const Point2f velocityPos{ utils::ToPoint2f(utils::GetAttributeValue("Posistion", stringData)) };
	m_Velocity = Vector2f{ velocityPos.x, velocityPos.y };
}
Pickup::Pickup(const Pickup& other)
	: Item(ItemType::pickup, other.m_Posistion, other.m_Width, other.m_Height)
	, m_Type{ other.m_Type }
	, m_EffectDuration{ other.m_EffectDuration }
	, m_EffectTimer{ 0 }
	, m_pAffectPlayer{ nullptr }
	, m_pTexture{ other.m_pTexture }
{
}
Pickup::~Pickup()
{
}

void Pickup::Draw() const
{
	if (m_PickedUp)
	{
		return;
	}
	m_pTexture->Draw(m_Posistion);
}
void Pickup::OnPickup(Player& player)
{
	// do things

	Item::OnPickup(player);
}