#pragma once
#include "MenuComponent.h"

class Player;
class Texture;

class HealthDisplay : public MenuComponent
{
public:
	HealthDisplay(Player* player, const Point2f& leftBottom);
	HealthDisplay(const HealthDisplay& other) = delete;
	HealthDisplay& operator=(const HealthDisplay& other) = delete;
	HealthDisplay(HealthDisplay&& other) = delete;
	HealthDisplay& operator=(HealthDisplay&& other) = delete;
	virtual ~HealthDisplay();

	virtual void Update(float elapsedsec) override;
	virtual void Draw() const override;

	virtual void OnClick(const Point2f& clickPos) override;
	virtual void OnPress(const SDL_KeyboardEvent& e) override;

	static const float m_TextureSpacing;
	static const float m_HitpointWidth;
	static const float m_HitpointHeight;

private:
	Player* m_pPlayer;
	const Point2f m_LeftBottom;
	Texture* m_pFullHitpointTexture;
	Texture* m_pEmptyHitpointTexture;
};

