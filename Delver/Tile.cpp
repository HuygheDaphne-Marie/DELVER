#include "pch.h"
#include "Tile.h"
#include "Texture.h"


const float Tile::m_Side = 32.f;

Tile::Tile(const GridPos& pos, Type tileType)
	: m_TilePos{pos}
	, m_Type{}
	, m_IsBarrier{}
	, m_pTexture{}
{
	SetType(tileType);
}
Tile::~Tile()
{
	m_pTexture = nullptr;
}

GridPos Tile::GetTilePos() const
{
	return m_TilePos;
}
Tile::Type Tile::GetType() const
{
	return m_Type;
}
bool Tile::IsBarrier() const
{
	return m_IsBarrier;
}
Point2f Tile::GetBottomLeft() const
{
	return Point2f{ m_TilePos.x * Tile::m_Side, m_TilePos.y * Tile::m_Side };
}
Texture* Tile::GetTexture() const
{
	return m_pTexture;
}
std::vector<Point2f> Tile::GetBarrier() const
{
	std::vector<Point2f> barrier{};
	const Point2f bottomLeft{ GetBottomLeft() };
	const float halfSide{ m_Side / 2 };
	switch (m_Type)
	{
	case Tile::Type::wall:
		{
			Point2f bottomRight{ bottomLeft.x + m_Side, bottomLeft.y };
			Point2f topRight{ bottomLeft.x + m_Side, bottomLeft.y + m_Side };
			Point2f topLeft{ bottomLeft.x, bottomLeft.y + m_Side };

			barrier.push_back(bottomLeft);
			barrier.push_back(bottomRight);
			barrier.push_back(topRight);
			barrier.push_back(topLeft);
		}
		break;
	case Tile::Type::wallSide:
		{
			Point2f topRight{ bottomLeft.x + m_Side, bottomLeft.y + m_Side };
			Point2f topLeft{ bottomLeft.x, bottomLeft.y + m_Side };
			Point2f middleLeft{ bottomLeft.x, bottomLeft.y + halfSide };
			Point2f middleRight{ bottomLeft.x + m_Side, bottomLeft.y + halfSide };

			barrier.push_back(middleLeft);
			barrier.push_back(middleRight);
			barrier.push_back(topRight);
			barrier.push_back(topLeft);
		}
		break;
	}
	return barrier;
}

void Tile::SetType(Type newType)
{
	m_Type = newType;
	switch (m_Type)
	{
	case Tile::Type::nothing:
		m_IsBarrier = true;
		break;
	case Tile::Type::wall:
		m_IsBarrier = true;
		break;
	case Tile::Type::wallSide:
		m_IsBarrier = true;
		break;
	case Tile::Type::floor:
		m_IsBarrier = false;
		break;
	}
}
void Tile::SetTexture(Texture* texture)
{
	m_pTexture = texture;
}

void Tile::Draw() const
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Draw(Rectf{ GetBottomLeft().x, GetBottomLeft().y, m_Side, m_Side });
		return;
	}

	switch (m_Type) // Temp
	{
	case Tile::Type::nothing:
		glColor3f(0, 0, 0);
		break;
	case Tile::Type::wall:
		glColor3f(0, 0.5f, 0.5f);
		break;
	case Tile::Type::floor:
		glColor3f(0.2f, 0.3f, 0);
		break;
	}
	utils::FillRect(Point2f{m_TilePos.x * m_Side, m_TilePos.y * m_Side}, m_Side, m_Side);
}
