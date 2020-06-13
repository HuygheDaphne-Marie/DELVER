#include "pch.h"
#include "HealthDisplay.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Player.h"

const float HealthDisplay::m_TextureSpacing = 10.f;
const float HealthDisplay::m_HitpointWidth = 30.f;
const float HealthDisplay::m_HitpointHeight = 30.f;

HealthDisplay::HealthDisplay(Player* player, const Point2f& leftBottom)
	: m_pPlayer{ player }
	, m_LeftBottom{ leftBottom }
	, m_pFullHitpointTexture{ TextureManager::GetInstance()->GetTexture("Resources/Textures/UI/heart.png") }
	, m_pEmptyHitpointTexture{ TextureManager::GetInstance()->GetTexture("Resources/Textures/UI/heart_empty.png") }
{
}
HealthDisplay::~HealthDisplay()
{
}

void HealthDisplay::Update(float elapsedsec)
{

}
void HealthDisplay::Draw() const
{
	Point2f drawPos{ m_LeftBottom };

	for (int i{0}; i < m_pPlayer->m_MaxHP; i++)
	{
		if (i < m_pPlayer->m_CurrentHp)
		{
			// draw full
			m_pFullHitpointTexture->Draw(Rectf{ drawPos.x, drawPos.y, m_HitpointWidth, m_HitpointHeight });
		}
		else
		{
			// draw empty
			m_pEmptyHitpointTexture->Draw(Rectf{ drawPos.x, drawPos.y, m_HitpointWidth, m_HitpointHeight });
		}
		drawPos.x += m_HitpointWidth + m_TextureSpacing;
	}
}

void HealthDisplay::OnClick(const Point2f& clickPos)
{
}
void HealthDisplay::OnPress(const SDL_KeyboardEvent& e)
{
}
