#pragma once
#include "Vector2f.h"

class Camera
{
public:
	Camera(float width, float height);
	
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	Vector2f GetClampDisplacement(const Point2f& centerTarget) const;
	
	void Transform(const Point2f& centerTarget) const;

private:
	const float m_Width;
	const float m_Height;
	Rectf m_LevelBoundaries;

	Point2f Track(const Point2f& centerTarget) const;
	void Clamp(Point2f& bottomLeftPos) const;
};

