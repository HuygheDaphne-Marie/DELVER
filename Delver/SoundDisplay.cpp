#include "pch.h"
#include "SoundDisplay.h"
#include "VolumeBtn.h"
#include "TextureManager.h"
#include "SoundManager.h"

const float SoundDisplay::m_ButtonSide = 32.f;
const float SoundDisplay::m_Spacing = 5.f;

SoundDisplay::SoundDisplay(const Point2f& leftBottom)
	: m_LeftBottom{leftBottom}
	, m_Printer{ "Resources/Textures/UI/VT323-Regular.ttf", int(m_ButtonSide) }
	, m_SubComponents{}
	, m_pVolumeIcon{ TextureManager::GetInstance()->GetTexture("Resources/Textures/UI/sound_icon.png") }
{
	const float wordWidth{ m_Printer.GetCharacterWidth() * 3 };

	const float offsetX{ m_ButtonSide + m_Spacing + wordWidth + m_Spacing};
	m_SubComponents.push_back(new VolumeBtn{ Rectf{leftBottom.x + offsetX, leftBottom.y, m_ButtonSide, m_ButtonSide} });
	m_SubComponents.push_back(new VolumeBtn{ Rectf{leftBottom.x + offsetX + m_ButtonSide + m_Spacing, leftBottom.y, m_ButtonSide, m_ButtonSide}, false });
}
SoundDisplay::~SoundDisplay()
{
	for (MenuComponent* component : m_SubComponents)
	{
		delete component;
	}
	m_SubComponents.clear();
}

void SoundDisplay::Update(float elapsedsec)
{
	for (MenuComponent* component : m_SubComponents)
	{
		component->Update(elapsedsec);
	}
}
void SoundDisplay::Draw() const
{
	m_pVolumeIcon->Draw(Rectf{ m_LeftBottom.x, m_LeftBottom.y, m_ButtonSide, m_ButtonSide });
	const Point2f textPos{ m_LeftBottom.x + m_ButtonSide + m_Spacing, m_LeftBottom.y };
	const int avgVolume{ (SoundManager::GetInstance()->GetStreamVolume() + SoundManager::GetInstance()->GetEffectsVolume()) / 2 };
	m_Printer.PrintString(std::to_string(avgVolume), textPos);
	for (MenuComponent* component : m_SubComponents)
	{
		component->Draw();
	}
}

void SoundDisplay::OnClick(const Point2f& clickPos)
{
	for (MenuComponent* component : m_SubComponents)
	{
		component->OnClick(clickPos);
	}
}
void SoundDisplay::OnPress(const SDL_KeyboardEvent& e)
{
	for (MenuComponent* component : m_SubComponents)
	{
		component->OnPress(e);
	}
}

