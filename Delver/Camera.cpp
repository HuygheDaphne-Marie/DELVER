#include "pch.h"
#include "Camera.h"
#include "utils.h"

Camera::Camera(float width, float height)
	: m_Width{ width }
	, m_Height{ height }
	, m_LevelBoundaries{ }
{
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}
Vector2f Camera::GetClampDisplacement(const Point2f& centerTarget) const
{
	const Point2f camPos{ Track(centerTarget) };
	Vector2f displacement{};

	if (camPos.x + m_Width > m_LevelBoundaries.left + m_LevelBoundaries.width)
	{
		displacement.x = (m_LevelBoundaries.left + m_LevelBoundaries.width) - (camPos.x + m_Width);
	}
	if (camPos.x < m_LevelBoundaries.left)
	{
		displacement.x = m_LevelBoundaries.left - camPos.x;
	}

	if (camPos.y + m_Height > m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		displacement.y = (m_LevelBoundaries.bottom + m_LevelBoundaries.height) - (camPos.y + m_Height);
	}
	if (camPos.y < m_LevelBoundaries.bottom)
	{
		displacement.y = m_LevelBoundaries.bottom - camPos.y;
	}

	return displacement;
}

void Camera::Transform(const Point2f& centerTarget) const
{
	Point2f camPos{ Track(centerTarget) };
	Clamp(camPos);

	glTranslatef(-camPos.x, -camPos.y, 0);
}

Point2f Camera::Track(const Point2f& centerTarget) const
{
	return Point2f{ centerTarget.x - m_Width / 2, centerTarget.y - m_Height / 2 };
}
void Camera::Clamp(Point2f& bottomLeftPos) const 
{
	// X-axis clamp
	if (bottomLeftPos.x + m_Width > m_LevelBoundaries.left + m_LevelBoundaries.width)
	{
		bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width;
	}
	if (bottomLeftPos.x < m_LevelBoundaries.left)
	{
		bottomLeftPos.x = m_LevelBoundaries.left;
	}

	// Y-Axis clamp
	if (bottomLeftPos.y + m_Height > m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height;
	}
	if (bottomLeftPos.y < m_LevelBoundaries.bottom)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom;
	}
}