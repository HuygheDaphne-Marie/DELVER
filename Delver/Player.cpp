#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include "Gun.h"
#include "TextureManager.h"
#include "PlayerKeyboardController.h"

#include "AnimatedTexture.h"
#include <iostream>

Player::Player(const Point2f& pos, Gun* pGunEquiped)
	: Actor
	(
		Actor::ActorData
		{ 
			pos, 
			Actor::Dimension{40.f, 40.f}, 
			Actor::Type::player, 
			TextureManager::GetInstance()->GetTexture("Resources/Textures/Actors/player.png") 
		}
	)
	, m_State{ State::waiting }
	, m_IdxEquippedGun{ 0 }
	, m_StartPosition{ pos }
	, m_AnimatedTexture{ "Resources/Textures/Actors/player.png" }
	, m_LookPos{ pos }
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
	if (m_pController != nullptr)
	{
		delete m_pController;
		m_pController = nullptr;
	}
}

void Player::Update(float elapsedSec, const Level& level, const Point2f mousePos)
{
	const Vector2f differenceFromStart{ m_StartPosition, GetPosition() };
	m_LookPos = mousePos + differenceFromStart;

	if (m_pGuns[m_IdxEquippedGun]->IsFiring())
	{
		if (m_State != State::firing)
		{
			SetState(Player::State::firing);
		}
		else
		{
			Animation* firingAnimation{ m_AnimatedTexture.GetCurrentAnimation() };
			if (firingAnimation->GetCurrentFrame() == firingAnimation->m_AmountOfFrames - 1)
			{
				firingAnimation->SetCurrentFrame(0);
			}
		}
	}

	m_AnimatedTexture.Update(elapsedSec);
	UpdateTextureStateString();

	if (m_pController != nullptr)
	{
		m_pController->Update(elapsedSec);
	}

	Actor::Update(elapsedSec, level);

	if (m_pGuns[m_IdxEquippedGun] != nullptr)
	{
		m_pGuns[m_IdxEquippedGun]->UpdateGun(elapsedSec);
		m_pGuns[m_IdxEquippedGun]->UpdateGunPos(m_Position);

		
		m_pGuns[m_IdxEquippedGun]->UpdateAimPos(m_LookPos);
	}
}
void Player::Draw() const
{
	if (m_pTexture != nullptr)
	{
		//Actor::Draw();
		glPushMatrix();
		{
			Rectf destRect{ m_Position.x - m_Width / 2, m_Position.y - m_Height / 2, m_Width, m_Height };
			if (m_Position.x > m_LookPos.x)
			{
				const std::string postfix{ GetStatePostfix() };
				if (postfix != "_up" && postfix != "_down")
				{
					glScalef(-1.f, 1.f, 1.f);
					destRect.left = -destRect.left - m_Width;
				}
			}
			
			m_AnimatedTexture.Draw(destRect);
		}
		glPopMatrix();
	}
	else
	{
		Actor::Draw();
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
	if (m_State == newstate)
	{
		return;
	}
	if (m_State == State::firing && !m_AnimatedTexture.GetCurrentAnimation()->IsAnimationDone())
	{
		return;
	}

	m_State = newstate;
}

Controller* Player::GetController() const
{
	return m_pController;
}
void Player::SetController(Controller* controller)
{
	if (m_pController != nullptr)
	{
		delete m_pController;
		m_pController = nullptr;
	}
	m_pController = controller;
}

void Player::UpdateTextureStateString()
{
	const std::string postfix{ GetStatePostfix() };

	switch (m_State)
	{
	case Player::State::waiting:
		m_AnimatedTexture.SetState("idle" + postfix);
		break;
	case Player::State::moving:
		m_AnimatedTexture.SetState("run" + postfix);
		break;
	case Player::State::firing:
	{
		m_AnimatedTexture.SetState("fire" + postfix);
	}
		break;
	case Player::State::dead:
		m_AnimatedTexture.SetState("dead");
		break;
	}
}

std::string Player::GetStatePostfix() const
{
	const float cirlce{ 360.f };
	const float angleStep{ 90.f / 4 }; // 4 divisions in a 90degree arc

	const Vector2f zeroDegreeVec{ 1, 0 };
	const Vector2f toMousePosVec{ m_Position, m_LookPos };
	float angle{ float(zeroDegreeVec.AngleWith(toMousePosVec) * (180.f / M_PI)) };

	if (angle > 90.f)
	{
		angle = 90.f - (angle - 90.f);
	}
	if (angle < -90.f)
	{
		angle = -90.f - (angle + 90.f); 
	}

	if (angle > (90.f - angleStep))
	{
		return "_up";
	}
	if (angle > (45.f - angleStep) && angle < (45.f + angleStep))
	{
		return "_up_side";
	}
	if (angle > (0.f - angleStep) && angle < (0.f + angleStep))
	{
		return "_side";
	}
	if (angle > (-45.f - angleStep) && angle < (-45.f + angleStep))
	{
		return "_down_side";
	}
	if (angle < (-90.f + angleStep))
	{
		return "_down";
	}
	return "";
}