#include "pch.h"
#include "RestartButton.h"

#include "Game.h"

RestartButton::RestartButton(Game* game, const Rectf& btnRect)
	: m_pGame{ game }
	, m_BtnRect{ btnRect }
	, m_Printer{ "Resources/Textures/UI/VT323-Regular.ttf", int(btnRect.height / 2) }
	, m_Text{ "Restart" }
	, m_pBtnTexture{ TextureManager::GetInstance()->GetTexture("Resources/Textures/UI/button_base.png") }
{
}
RestartButton::~RestartButton()
{
}

void RestartButton::Update(float elapsedsec)
{
}
void RestartButton::Draw() const
{
	m_pBtnTexture->Draw(m_BtnRect);

	const float wordWidth{ m_Text.size() * m_Printer.GetCharacterWidth() };
	const Point2f wordPos{ (m_BtnRect.left + m_BtnRect.width / 2) - wordWidth / 2, (m_BtnRect.bottom + m_BtnRect.height / 2) - m_Printer.GetCharacterHeight() / 2 };
	m_Printer.PrintString(m_Text, wordPos);
}

void RestartButton::OnClick(const Point2f& clickPos)
{
	if (utils::IsPointInRect(clickPos, m_BtnRect))
	{
		m_pGame->ResetGame();
	}
}
void RestartButton::OnPress(const SDL_KeyboardEvent& e)
{
}