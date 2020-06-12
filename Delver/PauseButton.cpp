#include "pch.h"
#include "PauseButton.h"
#include "Game.h"

PauseButton::PauseButton(Game* game, const Rectf& btnRect, const Color4f& btnColor)
	: m_pGame{ game }
	, m_BtnRect{ btnRect }
	, m_BtnColor{ btnColor }
{
}
PauseButton::~PauseButton()
{
}

void PauseButton::Update(float elapsedsec)
{
}
void PauseButton::Draw() const
{
	utils::SetColor(m_BtnColor);
	utils::FillRect(m_BtnRect);
	// TODO text
}

void PauseButton::OnClick(const Point2f& clickPos)
{
	if (utils::IsPointInRect(clickPos, m_BtnRect))
	{
		m_pGame->PauseGame();
	}
}
void PauseButton::OnPress(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_p || e.keysym.sym == SDLK_ESCAPE)
	{
		m_pGame->PauseGame();
	}
}