#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include "Gun.h"
#include "TextureManager.h"
#include "PlayerKeyboardController.h"

Player::Player(const Point2f& pos, Gun* pGunEquiped)
	: Actor(pos, Actor::Type::player, TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_PLAYER))
	, m_State{ State::waiting }
	, m_IdxEquippedGun{ 0 }
	, m_StartPosition{ pos }
{
	if (pGunEquiped != nullptr)
	{
		EquipGun(pGunEquiped);
	}
	SetController(new PlayerKeyboardController(this));
}
Player::~Player()
{
	for (Gun* gun : m_pGuns)
	{
		delete gun;
		gun = nullptr;
	}
}

void Player::Update(float elapsedSec, const Level& level, const Point2f mousePos)
{
	m_State = State::waiting;

	const float deltaVelocity{ m_Acceleration * elapsedSec };

	if (m_pController != nullptr)
	{
		m_pController->Update(elapsedSec);
	}

	Actor::Update(elapsedSec, level);

	if (m_pGuns[m_IdxEquippedGun] != nullptr)
	{
		m_pGuns[m_IdxEquippedGun]->UpdateGun(elapsedSec);
		m_pGuns[m_IdxEquippedGun]->UpdateGunPos(m_Position);

		Vector2f differenceFromStart{ m_StartPosition, GetPosition() };
		m_pGuns[m_IdxEquippedGun]->UpdateAimPos(mousePos + differenceFromStart);
	}
}
void Player::Draw() const
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Draw(Point2f{ m_Position.x - m_pTexture->GetWidth() / 2, m_Position.y - m_pTexture->GetHeight() / 2 });
	}
	else
	{
		Actor::Draw();
	}

	// make sure to draw in propper order:
	//	- if moving up then player on top and gun below
	//	- if moving down then gun on top player bottom
	//	- see if you can make left/right not matter for order?

	if (m_pGuns[m_IdxEquippedGun] != nullptr)
	{
		m_pGuns[m_IdxEquippedGun]->Draw();
	}
}

void Player::EquipGun(Gun* pGunToEquip)
{
	if (pGunToEquip == nullptr)
	{
		return;
	}

	m_pGuns.push_back(pGunToEquip);
	if (m_pGuns.size() == 1)
	{
		m_IdxEquippedGun = 0;
		m_pGuns[m_IdxEquippedGun]->SetHolder(this);
	}
}
void Player::SwapGun(bool swappingToNext)
{
	m_pGuns[m_IdxEquippedGun]->SetHolder(nullptr);
	if (swappingToNext)
	{
		m_IdxEquippedGun++;
	}
	else
	{
		m_IdxEquippedGun--;
	}
	m_pGuns[m_IdxEquippedGun]->SetHolder(this);

	if (m_IdxEquippedGun >= m_pGuns.size())
	{
		m_IdxEquippedGun = 0;
	}
	else if (m_IdxEquippedGun < 0)
	{
		m_IdxEquippedGun = m_pGuns.size() - 1;
	}
}
Gun* Player::GetEquippedGun() const
{
	return m_pGuns[m_IdxEquippedGun];
}

void Player::SetState(const State& newstate)
{
	m_State = newstate;
}