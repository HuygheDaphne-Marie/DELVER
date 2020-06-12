#include "pch.h"
#include "PickupDisplay.h"

#include "Player.h"
#include "Pickup.h"

const float PickupDisplay::m_CircleRadius = 30.f;

PickupDisplay::PickupDisplay(Player* player, const Point2f& center, const Color4f& circleColor)
	: m_pPlayer{player}
	, m_Center{ center }
	, m_CircleColor{circleColor}
{
}
PickupDisplay::~PickupDisplay()
{
}

void PickupDisplay::Update(float elapsedsec)
{

}
void PickupDisplay::Draw() const
{
	Pickup* pickup{ m_pPlayer->GetPickup() };
	if (pickup != nullptr)
	{
		DrawCircle();
		//pickup-> // get texture and put in middle of circle
	}
	// circle with texture in the middle, which becomes smaller as there is less time left
}

void PickupDisplay::OnClick(const Point2f& clickPos)
{
}
void PickupDisplay::OnPress(const SDL_KeyboardEvent& e)
{
}

void PickupDisplay::DrawCircle() const
{
	Pickup* pickup{ m_pPlayer->GetPickup() };
	const float fractionTimeLeft{ pickup->GetEffectTimer() / pickup->GetEffectDuration() };
	
	const float startRad{ float(M_PI / 2) };
	std::vector<Point2f> circlePoints{};

	// non full part
	circlePoints.push_back(m_Center);
	for (float rad{ 0 }; rad < (M_PI * 2 * fractionTimeLeft); rad += float(M_PI / 180))
	{
		circlePoints.push_back(Point2f{ m_Center.x + float(cos(rad + startRad) * m_CircleRadius), m_Center.y + float(sin(rad + startRad) * m_CircleRadius) });
	}
	circlePoints.push_back(m_Center);


	utils::SetColor(Color4f{ m_CircleColor.r, m_CircleColor.g, m_CircleColor.b, m_CircleColor.a / 2 });
	utils::FillPolygon(circlePoints);
	circlePoints.clear();


	// full part
	circlePoints.push_back(m_Center);
	for (float rad{ float(M_PI * 2) * fractionTimeLeft }; rad < (M_PI * 2); rad += float(M_PI / 180))
	{
		circlePoints.push_back(Point2f{ m_Center.x + float(cos(rad + startRad) * m_CircleRadius), m_Center.y + float(sin(rad + startRad) * m_CircleRadius) });
	}
	circlePoints.push_back(m_Center);

	utils::SetColor(m_CircleColor);
	utils::FillPolygon(circlePoints);
}