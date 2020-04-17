#pragma once
#include "Vector2f.h"

class Camera
{
public:
	Camera(float width, float height, float wiggleWidth, float wiggleHeight, const Point2f& centerPos);
	
	void SetCenterPos(const Point2f& centerPos);
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	Vector2f GetClampDisplacement(const Point2f& centerTarget) const;
	
	void UpdatePos(const Point2f& centerTarget);
	void Transform() const;

private:
	const float m_Width;
	const float m_Height;
	Rectf m_LevelBoundaries;
	Point2f m_CenterPos;
	const float m_WiggleWidth; // Coolest name for a variable
	const float m_WiggleHeight;

	Vector2f Track(const Point2f& centerTarget) const;
	void Clamp(Point2f& bottomLeftPos) const;
};

