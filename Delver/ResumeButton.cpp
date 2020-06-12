#include "pch.h"
#include "ResumeButton.h"
#include "Game.h"

ResumeButton::ResumeButton(Game* game, const Rectf& btnRect, const Color4f& btnColor)
	: m_pGame{ game }
	, m_BtnRect{ btnRect }
	, m_BtnColor{ btnColor }
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
	utils::SetColor(m_BtnColor);
	utils::FillRect(m_BtnRect);
	// TODO text
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