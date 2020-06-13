#pragma once
#include "MenuComponent.h"
#include "StringPrinter.h"

class Game;

class ResumeButton : public MenuComponent
{
public:
	ResumeButton(Game* game, const Rectf& btnRect);
	ResumeButton(const ResumeButton& other) = delete;
	ResumeButton& operator=(const ResumeButton& other) = delete;
	ResumeButton(ResumeButton&& other) = delete;
	ResumeButton& operator=(ResumeButton&& other) = delete;
	virtual ~ResumeButton();

	virtual void Update(float elapsedsec) override;
	virtual void Draw() const override;

	virtual void OnClick(const Point2f& clickPos) override;
	virtual void OnPress(const SDL_KeyboardEvent& e) override;

private:
	Game* m_pGame;
	const Rectf m_BtnRect;
	StringPrinter m_Printer;
	const std::string m_Text;
	Texture* m_pBtnTexture;
};

