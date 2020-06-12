#include "pch.h"
#include "FloorDisplay.h"

#include "Level.h"

FloorDisplay::FloorDisplay(Level* level, const Point2f& leftBottom)
	: m_pLevel{level}
	, m_DrawPos{leftBottom}
	, m_Printer{"Resources/Textures/UI/VT323-Regular.ttf", 50}
{
}
FloorDisplay::~FloorDisplay()
{
}

void FloorDisplay::Update(float elapsedsec)
{
}
void FloorDisplay::Draw() const
{
	m_Printer.PrintString("Floor: " + std::to_string(m_pLevel->GetCurrentLevel()), m_DrawPos);
}

void FloorDisplay::OnClick(const Point2f& clickPos)
{
}
void FloorDisplay::OnPress(const SDL_KeyboardEvent& e)
{
}