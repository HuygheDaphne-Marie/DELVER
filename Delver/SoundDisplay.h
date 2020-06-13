#pragma once
#include "MenuComponent.h"
#include "StringPrinter.h"

#include "Texture.h"

class SoundDisplay : public MenuComponent
{
public:
	SoundDisplay(const Point2f& leftBottom);
	SoundDisplay(const SoundDisplay& other) = delete;
	SoundDisplay& operator=(const SoundDisplay& other) = delete;
	SoundDisplay(SoundDisplay&& other) = delete;
	SoundDisplay& operator=(SoundDisplay&& other) = delete;
	~SoundDisplay();

	virtual void Update(float elapsedsec) override;
	virtual void Draw() const override;

	virtual void OnClick(const Point2f& clickPos) override;
	virtual void OnPress(const SDL_KeyboardEvent& e) override;

	static const float m_ButtonSide;
	static const float m_Spacing;

private:
	std::vector<MenuComponent*> m_SubComponents;
	StringPrinter m_Printer;
	const Point2f m_LeftBottom;

	Texture* m_pVolumeIcon;
};

