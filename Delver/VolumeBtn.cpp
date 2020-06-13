#include "pch.h"
#include "VolumeBtn.h"

#include "TextureManager.h"
#include "SoundManager.h"

const int VolumeBtn::m_VolumeStep = 10;

VolumeBtn::VolumeBtn(const Rectf& btnRect, bool increaseBtn)
	: m_BtnRect{btnRect}
	, m_pBtnTexture{ nullptr }
	, m_IncreasesVolume{ increaseBtn }
{
	if (m_IncreasesVolume)
	{
		m_pBtnTexture = TextureManager::GetInstance()->GetTexture("Resources/Textures/UI/button_plus.png");
	}
	else
	{
		m_pBtnTexture = TextureManager::GetInstance()->GetTexture("Resources/Textures/UI/button_minus.png");
	}
}
VolumeBtn::~VolumeBtn()
{
}

void VolumeBtn::Update(float elapsedsec)
{
}
void VolumeBtn::Draw() const
{
	m_pBtnTexture->Draw(m_BtnRect);
}

void VolumeBtn::OnClick(const Point2f& clickPos)
{
	if (utils::IsPointInRect(clickPos, m_BtnRect))
	{
		if (m_IncreasesVolume)
		{
			SoundManager::GetInstance()->SetEffectsVolume(SoundManager::GetInstance()->GetEffectsVolume() + m_VolumeStep);
			SoundManager::GetInstance()->SetStreamVolume(SoundManager::GetInstance()->GetStreamVolume() + m_VolumeStep);
		}
		else
		{
			SoundManager::GetInstance()->SetEffectsVolume(SoundManager::GetInstance()->GetEffectsVolume() - m_VolumeStep);
			SoundManager::GetInstance()->SetStreamVolume(SoundManager::GetInstance()->GetStreamVolume() - m_VolumeStep);
		}
	}
}
void VolumeBtn::OnPress(const SDL_KeyboardEvent& e)
{
}
