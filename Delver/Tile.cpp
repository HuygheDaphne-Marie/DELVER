#include "pch.h"
#include "Tile.h"

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

void Tile::SetType(Type newType)
{
	m_Type = newType;
	switch (m_Type)
	{
	case Tile::Type::nothing:
		m_pTexture = nullptr;
		m_IsWalkable = false;
		break;
	case Tile::Type::wall:
		m_pTexture = nullptr; // Get wall texture from manager
		m_IsWalkable = false;
		break;
	case Tile::Type::floor:
		m_pTexture = nullptr; // Get floor texture from manager
		m_IsWalkable = true;
		break;
	}
}

void Tile::Draw() const
{
	switch (m_Type) // Temp
	{
	case Tile::Type::nothing:
		glColor3f(0, 0, 0);
		break;
	case Tile::Type::wall:
		glColor3f(1, 0, 0);
		break;
	case Tile::Type::floor:
		glColor3f(0, 1, 0);
		break;
	}
	utils::FillRect(Point2f{m_TilePos.x * m_Side, m_TilePos.y * m_Side}, m_Side, m_Side);
}
