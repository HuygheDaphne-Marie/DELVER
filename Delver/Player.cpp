#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include "Gun.h"

Player::Player(const Point2f& pos, Gun* pGunEquiped)
	: Actor(pos, Actor::Type::player)
	, m_State{ State::waiting }
	, m_IdxEquippedGun{ 0 }
	, m_StartPosition{ pos }
{
	if (pGunEquiped != nullptr)
	{
		EquipGun(pGunEquiped);
	}
}
Player::~Player()
{
	for (Gun* gun : m_pGuns)
	{
		delete gun;
		gun = nullptr;
	}
}

void Player::Update(float elapsedSec)
{
	Update(elapsedSec, Point2f{ 0, 0 });
}
void Player::Update(float elapsedSec, const Point2f mousePos)
{
	m_Velocity.x = 0;
	m_Velocity.y = 0;
	m_State = State::waiting;

	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if ( pStates[SDL_SCANCODE_A] )
	{
		m_Velocity.x = -m_Speed;
		m_State = State::moving;
	}
	if ( pStates[SDL_SCANCODE_D])
	{
		m_Velocity.x = m_Speed;
		m_State = State::moving;
	}
	if (pStates[SDL_SCANCODE_W])
	{
		m_Velocity.y = m_Speed;
		m_State = State::moving;
	}
	if (pStates[SDL_SCANCODE_S])
	{
		m_Velocity.y = -m_Speed;
		m_State = State::moving;
	}

	Actor::Update(elapsedSec);
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
	}
}
void Player::SwapGun(bool swappingToNext)
{
	if (swappingToNext)
	{
		m_IdxEquippedGun++;
	}
	else
	{
		m_IdxEquippedGun--;
	}

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