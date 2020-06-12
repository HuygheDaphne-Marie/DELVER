#pragma once
#include "MenuComponent.h"

class Game;

class PauseButton : public MenuComponent
{
public:
	PauseButton(Game* game, const Rectf& btnRect, const Color4f& btnColor);
	PauseButton(const PauseButton& other) = delete;
	PauseButton& operator=(const PauseButton& other) = delete;
	PauseButton(PauseButton&& other) = delete;
	PauseButton& operator=(PauseButton&& other) = delete;
	virtual ~PauseButton();

	virtual void Update(float elapsedsec) override;
	virtual void Draw() const override;

	virtual void OnClick(const Point2f& clickPos) override;
	virtual void OnPress(const SDL_KeyboardEvent& e) override;

private:
	Game* m_pGame;
	const Rectf m_BtnRect;
	const Color4f m_BtnColor;
};

