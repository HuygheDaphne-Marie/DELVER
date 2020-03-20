#include "pch.h"
#include "Room.h"
#include "utils.h"

Room::Room(const GridPos& position)
	: m_RoomPos{position}
	, m_BottomLeft{ position.x * (m_RoomCols * Tile::m_Side), position.y * (m_RoomCols * Tile::m_Side) }
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
		GridPos tilePos{ utils::GridPosFromIndex(i, m_RoomCols) };
		m_Tiles.push_back(Tile(tilePos, Tile::Type::floor));
	}

	GenerateEdges();

	m_IsGenerated = true;
}
void Room::GenerateEdges()
{
	for (int i{}; i < m_RoomCols; i++)
	{
		m_Tiles[utils::IndexFromGridPos(GridPos{ i, 0 }, m_RoomCols)].SetType(Tile::Type::wall);
		m_Tiles[utils::IndexFromGridPos(GridPos{ i, m_RoomRows - 1 }, m_RoomCols)].SetType(Tile::Type::wall);
	}
	for (int i{}; i < m_RoomRows; i++)
	{
		m_Tiles[utils::IndexFromGridPos(GridPos{ 0, i }, m_RoomCols)].SetType(Tile::Type::wall);
		m_Tiles[utils::IndexFromGridPos(GridPos{ m_RoomCols - 1, i }, m_RoomCols)].SetType(Tile::Type::wall);
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
		m_Tiles[utils::IndexFromGridPos(hallwayStart, m_RoomCols)].SetType(Tile::Type::floor);
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

void Room::Draw() const
{
	if (!m_IsGenerated)
	{
		return;
	}

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
