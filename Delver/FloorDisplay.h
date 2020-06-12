#pragma once
#include "MenuComponent.h"
#include "StringPrinter.h"

class Level;

class FloorDisplay : public MenuComponent
{
public:
	FloorDisplay(Level* level, const Point2f& leftBottom);
	FloorDisplay(const FloorDisplay& other) = delete;
	FloorDisplay& operator=(const FloorDisplay& other) = delete;
	FloorDisplay(FloorDisplay&& other) = delete;
	FloorDisplay& operator=(FloorDisplay&& other) = delete;
	virtual ~FloorDisplay();

	virtual void Update(float elapsedsec) override;
	virtual void Draw() const override;

	virtual void OnClick(const Point2f& clickPos) override;
	virtual void OnPress(const SDL_KeyboardEvent& e) override;

private:
	Level* m_pLevel;
	const Point2f m_DrawPos;
	StringPrinter m_Printer;
};

