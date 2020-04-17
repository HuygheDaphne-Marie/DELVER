#include "pch.h"
#include "Camera.h"
#include "utils.h"

Camera::Camera(float width, float height, float wiggleWidth, float wiggleHeight, const Point2f& centerPos)
	: m_Width{ width }
	, m_Height{ height }
	, m_WiggleWidth{ wiggleWidth }
	, m_WiggleHeight{ wiggleHeight }
	, m_LevelBoundaries{ }
	, m_CenterPos{ centerPos }
{
}

void Camera::SetCenterPos(const Point2f& centerPos)
{
	m_CenterPos = centerPos;
}
void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}
Vector2f Camera::GetClampDisplacement(const Point2f& centerTarget) const
{
	const Point2f camPos{ m_CenterPos.x - m_Width / 2, m_CenterPos.y - m_Height / 2 };
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

	return displacement - Vector2f{ m_CenterPos, centerTarget };
}

void Camera::UpdatePos(const Point2f& centerTarget)
{
	Vector2f displacement{ Track(centerTarget) };
	m_CenterPos += displacement;

}

void Camera::Transform() const
{
	Point2f cameraPos{ m_CenterPos.x - m_Width / 2, m_CenterPos.y - m_Height / 2 };
	Clamp(cameraPos);

	glTranslatef(-cameraPos.x, -cameraPos.y, 0);
}

Vector2f Camera::Track(const Point2f& centerTarget) const
{
	const Rectf wiggleRect{ m_CenterPos.x - m_WiggleWidth / 2, m_CenterPos.y - m_WiggleHeight / 2, m_WiggleWidth, m_WiggleHeight };

	if (!utils::IsPointInRect(centerTarget, wiggleRect))
	{
		const std::vector<Point2f> wiggleRectVerticies
		{
			Point2f{m_CenterPos.x - m_WiggleWidth / 2, m_CenterPos.y - m_WiggleHeight / 2},
			Point2f{m_CenterPos.x + m_WiggleWidth / 2, m_CenterPos.y - m_WiggleHeight / 2},
			Point2f{m_CenterPos.x + m_WiggleWidth / 2, m_CenterPos.y + m_WiggleHeight / 2},
			Point2f{m_CenterPos.x - m_WiggleWidth / 2, m_CenterPos.y + m_WiggleHeight / 2},
			Point2f{m_CenterPos.x - m_WiggleWidth / 2, m_CenterPos.y - m_WiggleHeight / 2},
		};

		utils::HitInfo hitInfo{};
		utils::Raycast(wiggleRectVerticies, m_CenterPos, centerTarget, hitInfo);

		return Vector2f{ m_CenterPos, centerTarget } * (1 - hitInfo.lambda);
	}
	return Vector2f{ 0, 0 };
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