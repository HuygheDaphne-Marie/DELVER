#include "pch.h"
#include "Room.h"

Room::Room(const GridPos& position, const Point2f& bottomLeft)
	: m_RoomPos{position}
	, m_BottomLeft{bottomLeft}
	, m_Tiles{}
	, m_IsTopOpen{false}
	, m_IsLeftOpen{false}
	, m_IsBottomOpen{false}
	, m_IsRightOpen{false}
	, m_IsGenerated{false}
{
}
Room::~Room()
{
}

void Room::Generate()
{
	for (int i{}; i < (m_RoomCols * m_RoomRows); i++)
	{
		GridPos tilePos{ GridPosFromIndex(i) };
		m_Tiles.push_back(Tile(tilePos, Tile::Type::floor));
	}

	GenerateEdges();

	m_IsGenerated = true;
}

void Room::Draw() const
{
	glPushMatrix();
	glTranslatef(m_BottomLeft.x, m_BottomLeft.y, 0);
	for (Tile tile : m_Tiles)
	{
		tile.Draw();
	}
	glPopMatrix();
}

std::vector<Point2f> Room::GetBarriers() const
{
	return std::vector<Point2f>{}; // TEMP
}

void Room::SetConnection(bool shouldTopOpen, bool shouldLeftOpen, bool shouldBottomOpen, bool shouldRightOpen)
{
	m_IsTopOpen = shouldTopOpen;
	m_IsLeftOpen = shouldLeftOpen;
	m_IsBottomOpen = shouldBottomOpen;
	m_IsRightOpen = shouldRightOpen;
}

GridPos Room::GridPosFromIndex(int index) const
{
	return GridPos{ index % m_RoomCols, index / m_RoomCols };
}
int Room::IndexFromGridPos(const GridPos& tilePos) const
{
	return tilePos.y * m_RoomCols + tilePos.x;
}

void Room::GenerateEdges()
{
	for (int i{}; i < m_RoomCols; i++)
	{
		m_Tiles[IndexFromGridPos(GridPos{ i, 0 })].SetType(Tile::Type::wall);
		m_Tiles[IndexFromGridPos(GridPos{ i, m_RoomRows - 1 })].SetType(Tile::Type::wall);
	}
	for (int i{}; i < m_RoomRows; i++)
	{
		m_Tiles[IndexFromGridPos(GridPos{ 0, i })].SetType(Tile::Type::wall);
		m_Tiles[IndexFromGridPos(GridPos{ m_RoomCols - 1, i })].SetType(Tile::Type::wall);
	}

	if (m_IsTopOpen)
	{
		GridPos hallwayTile{ (m_RoomCols - m_HallwayWidth + 1) / 2, m_RoomRows - 1 };
		GenerateHallway(hallwayTile, true);
	}
	if (m_IsBottomOpen)
	{
		GridPos hallwayTile{ (m_RoomCols - m_HallwayWidth + 1) / 2, 0 };
		GenerateHallway(hallwayTile, true);
	}

	if (m_IsLeftOpen)
	{
		GridPos hallwayTile{ 0, (m_RoomRows - m_HallwayWidth + 1) / 2 };
		GenerateHallway(hallwayTile, false);
	}
	if (m_IsRightOpen)
	{
		GridPos hallwayTile{ m_RoomCols - 1, (m_RoomRows - m_HallwayWidth + 1) / 2 };
		GenerateHallway(hallwayTile, false);
	}
}
void Room::GenerateHallway(GridPos& hallwayStart, bool isHorizontal)
{
	for (int i{}; i < m_HallwayWidth; i++)
	{
		m_Tiles[IndexFromGridPos(hallwayStart)].SetType(Tile::Type::floor);
		if (isHorizontal)
		{
			hallwayStart.x++;
		}
		else
		{
			hallwayStart.y++;
		}
	}
}