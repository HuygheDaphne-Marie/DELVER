#include "pch.h"
#include "ResumeButton.h"
#include "Game.h"

#include "TextureManager.h"

ResumeButton::ResumeButton(Game* game, const Rectf& btnRect)
	: m_pGame{ game }
	, m_BtnRect{ btnRect }
	, m_Printer{ "Resources/Textures/UI/VT323-Regular.ttf", 30 }
	, m_Text{ "Resume" }
	, m_pBtnTexture{ TextureManager::GetInstance()->GetTexture("Resources/Textures/UI/button_base.png") }
{
}
ResumeButton::~ResumeButton()
{
}

void ResumeButton::Update(float elapsedsec)
{
}
void ResumeButton::Draw() const
{
	//utils::FillRect(m_BtnRect);
	m_pBtnTexture->Draw(m_BtnRect);
	
	const float wordWidth{ m_Text.size() * m_Printer.GetCharacterWidth() };
	const Point2f wordPos{ (m_BtnRect.left + m_BtnRect.width / 2) - wordWidth / 2, (m_BtnRect.bottom + m_BtnRect.height / 2) - m_Printer.GetCharacterHeight() / 2 };
	m_Printer.PrintString(m_Text, wordPos);
}

void ResumeButton::OnClick(const Point2f& clickPos)
{
	if (utils::IsPointInRect(clickPos, m_BtnRect))
	{
		m_pGame->ResumeGame();
	}
}
void ResumeButton::OnPress(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_r || e.keysym.sym == SDLK_ESCAPE)
	{
		m_pGame->ResumeGame();
	}
}