#pragma once
#include "MenuComponent.h"

class Game;
#include "StringPrinter.h"

class RestartButton : public MenuComponent
{
public:
	RestartButton(Game* game, const Rectf& btnRect, const Color4f& btnColor = Color4f{ 0,0,0,1 });
	RestartButton(const RestartButton& other) = delete;
	RestartButton& operator=(const RestartButton& other) = delete;
	RestartButton(RestartButton&& other) = delete;
	RestartButton& operator=(RestartButton&& other) = delete;
	virtual ~RestartButton();

	virtual void Update(float elapsedsec) override;
	virtual void Draw() const override;

	virtual void OnClick(const Point2f& clickPos) override;
	virtual void OnPress(const SDL_KeyboardEvent& e) override;

private:
	Game* m_pGame;
	const Rectf m_BtnRect;
	const Color4f m_BtnColor;
	StringPrinter m_Printer;
	const std::string m_Text;
};

