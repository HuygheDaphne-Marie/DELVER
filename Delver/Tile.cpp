#include "pch.h"
#include "Tile.h"
#include "Texture.h"


const float Tile::m_Side = 32.f;

Tile::Tile(const GridPos& pos, Type tileType)
	: m_TilePos{pos}
	, m_Type{}
	, m_IsWalkable{}
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
bool Tile::IsWalkable() const
{
	return m_IsWalkable;
}
Point2f Tile::GetBottomLeft() const
{
	return Point2f{ m_TilePos.x * Tile::m_Side, m_TilePos.y * Tile::m_Side };
}

void Tile::SetType(Type newType)
{
	m_Type = newType;
	switch (m_Type)
	{
	case Tile::Type::nothing:
		m_IsWalkable = false;
		break;
	case Tile::Type::wall:
		m_IsWalkable = false;
		break;
	case Tile::Type::wallSide:
		m_IsWalkable = true;
		break;
	case Tile::Type::floor:
		m_IsWalkable = true;
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


