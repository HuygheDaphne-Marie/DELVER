#pragma once
#include "MenuComponent.h"

class Player;

class PickupDisplay : public MenuComponent
{
public:
	PickupDisplay(Player* player, const Point2f& center, const Color4f& circleColor = Color4f{1, 1, 1, 1});
	virtual ~PickupDisplay();

	virtual void Update(float elapsedsec) override;
	virtual void Draw() const override;

	virtual void OnClick(const Point2f& clickPos) override;
	virtual void OnPress(const SDL_KeyboardEvent& e) override;

	static const float m_CircleRadius;

private:
	Player* m_pPlayer;
	const Point2f m_Center;
	const Color4f m_CircleColor;
	
	void DrawCircle() const;
};

