#include "pch.h"
#include "Pickup.h"

#include "TextureManager.h"
#include <sstream>

#include "Gun.h"
#include "SpecialEffect.h"
#include "ItemManager.h"

#include "SoundManager.h"

Pickup::Pickup(PickupType type, float effectDuration, const Point2f& pos, const Vector2f& velocity)
	: Item(ItemType::pickup, pos, velocity)
	, m_Type{ type }
	, m_EffectDuration{ effectDuration }
	, m_EffectTimer{ 0 }
	, m_pAffectedPlayer{ nullptr }
	, m_pTexture{ nullptr }
	, m_EffectActive{ false }
	, m_pPickupSound{ SoundManager::GetInstance()->GetSoundEffect("Resources/Sound/Pickup.wav") }
{
	switch (type)
	{
	case PickupType::bounce:
		m_pTexture = TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Pickup_Bounce);
		break;
	case PickupType::warp: 
		m_pTexture = TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Pickup_Warp);
		break;
	case PickupType::health:
		m_pTexture = TextureManager::GetInstance()->GetTexture("Resources/Textures/Items/Health.png");
		break;
	}
}
Pickup::Pickup(const std::string& stringData)
	: Item(ItemType::pickup, Point2f{0,0})
	, m_Type{ PickupType::bounce }
	, m_EffectDuration{ 0 }
	, m_EffectTimer{ 0 }
	, m_pAffectedPlayer{ nullptr }
	, m_pTexture{ nullptr }
	, m_EffectActive{ false }
	, m_pPickupSound{ SoundManager::GetInstance()->GetSoundEffect("Resources/Sound/Pickup.wav") }
{
	std::string type{ utils::GetAttributeValue("Type", stringData) };
	if (type == "bounce")
	{
		m_Type = PickupType::bounce;
		m_pTexture = TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Pickup_Bounce);
	}
	else if (type == "warp")
	{
		m_Type = PickupType::warp;
		m_pTexture = TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Pickup_Warp);
	}
	else if (type == "health")
	{
		m_Type = PickupType::health;
		m_pTexture = TextureManager::GetInstance()->GetTexture("Resources/Textures/Items/Health.png");
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
	: Item(ItemType::pickup, other.m_Posistion, other.m_Velocity)
	, m_Type{ other.m_Type }
	, m_EffectDuration{ other.m_EffectDuration }
	, m_EffectTimer{ 0 }
	, m_pAffectedPlayer{ nullptr }
	, m_pTexture{ other.m_pTexture }
	, m_EffectActive{ false }
	, m_pPickupSound{ SoundManager::GetInstance()->GetSoundEffect("Resources/Sound/Pickup.wav") }
{
}
Pickup::~Pickup()
{
	m_pAffectedPlayer = nullptr;
	m_pTexture = nullptr;
}

void Pickup::Update(float elapsedSec, Player& player)
{
	if (m_EffectActive)
	{
		m_EffectTimer += elapsedSec;
		if (m_EffectTimer > m_EffectDuration)
		{
			StopEffect();
		}
	}

	Item::Update(elapsedSec, player);
}
void Pickup::Draw() const
{
	if (m_PickedUp)
	{
		return;
	}
	m_pTexture->Draw(Rectf{ m_Posistion.x, m_Posistion.y, m_Width, m_Height});
}
void Pickup::OnPickup(Player& player)
{
	if (m_PickedUp)
	{
		return;
	}

	SoundManager::GetInstance()->PlaySoundEffect(m_pPickupSound);

	m_pAffectedPlayer = &player;
	StartEffect();
	
	// check if player has active powerup
		// if so stop it and delete it
	// tell player to start this power up

	// Player will need: bool HasActivePickup(), void Start/StopPickup, and a ptr to the pickup
	
	// cleanest would be: 
	// 1. stop other pickups
	// 2. get player's gun
	// 3. set effect on gun

	// this way pickup would need to be the one which sets and unsets the effect on the player, so Pickup would need a start and end function

	Item::OnPickup(player);
}

void Pickup::StartEffect()
{
	if (m_pAffectedPlayer != nullptr)
	{
		SpecialEffect::Type effectToBeApplied{};

		switch (m_Type)
		{
		case Pickup::PickupType::bounce:
			effectToBeApplied = SpecialEffect::Type::bounce;
			break;
		case Pickup::PickupType::warp:
			effectToBeApplied = SpecialEffect::Type::warp;
			break;
		case Pickup::PickupType::health:
			m_pAffectedPlayer->m_CurrentHp++;
			ItemManager::GetInstance()->QueueForDestroy(this);
			return;
			break;
		}

		m_pAffectedPlayer->SetPickup(nullptr);
		m_pAffectedPlayer->GetEquippedGun()->m_TypeOfSpecialEffectLoaded = effectToBeApplied;
		m_EffectActive = true;
		m_pAffectedPlayer->SetPickup(this);
	}
}
void Pickup::StopEffect()
{
	if (m_pAffectedPlayer != nullptr)
	{
		m_pAffectedPlayer->GetEquippedGun()->m_TypeOfSpecialEffectLoaded = SpecialEffect::Type::none;
		m_EffectActive = false;
		m_pAffectedPlayer->SetPickup(nullptr);
		ItemManager::GetInstance()->QueueForDestroy(this);
		m_pAffectedPlayer = nullptr;
	}
}

const float Pickup::GetEffectDuration() const
{
	return m_EffectDuration;
}
const float Pickup::GetEffectTimer() const
{
	return m_EffectTimer;
}
const Texture* Pickup::GetTexture() const
{
	return m_pTexture;
}