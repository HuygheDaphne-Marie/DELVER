#include "pch.h"
#include "Room.h"
#include "utils.h"

const int Room::m_RoomCols = 9;
const int Room::m_RoomRows = 9;
const int Room::m_HallwayWidth = 3;

Room::Room(const GridPos& position)
	: m_RoomPos{position}
	, m_BottomLeft{ position.x * (m_RoomCols * Tile::m_Side), position.y * (m_RoomCols * Tile::m_Side) }
	, m_Tiles{}
	, m_IsTopOpen{false}
	, m_IsLeftOpen{false}
	, m_IsBottomOpen{false}
	, m_IsRightOpen{false}
	, m_IsGenerated{false}
	, m_Barriers{}
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
	InitBarriers();
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
		for (std::vector<Point2f> barrier : m_Barriers)
		{
			glColor3f(1.f, 1.f, 1.f);
			utils::DrawPolygon(barrier, false);
		}
	}
	glPopMatrix();
}

void Room::InitBarriers()
{
	for (Tile tile : m_Tiles)
	{
		if (!tile.IsWalkable())
		{
			std::vector<Point2f> tileBarrier{};
			GridPos tilePos{ tile.GetTilePos() };
			GridPos otherTilePos{ tilePos.x + 1, tilePos.y };

			// Left & right
			if (utils::GridPosValid(otherTilePos, m_RoomCols, m_RoomRows) && m_Tiles[utils::IndexFromGridPos(otherTilePos, m_RoomCols)].IsWalkable())
			{
				// Barrier on right side
				tileBarrier.push_back(Point2f{ tile.GetBottomLeft().x + Tile::m_Side, tile.GetBottomLeft().y });
				tileBarrier.push_back(Point2f{ tile.GetBottomLeft().x + Tile::m_Side, tile.GetBottomLeft().y + Tile::m_Side });
			}
			otherTilePos.x = tilePos.x - 1;
			if (utils::GridPosValid(otherTilePos, m_RoomCols, m_RoomRows) && m_Tiles[utils::IndexFromGridPos(otherTilePos, m_RoomCols)].IsWalkable())
			{
				// Barrier on left side
				tileBarrier.push_back(tile.GetBottomLeft());
				tileBarrier.push_back(Point2f{ tile.GetBottomLeft().x, tile.GetBottomLeft().y + Tile::m_Side });
			}

			otherTilePos.x = tilePos.x;

			// Top & bottom
			otherTilePos.y = tilePos.y + 1;
			if (utils::GridPosValid(otherTilePos, m_RoomCols, m_RoomRows) && m_Tiles[utils::IndexFromGridPos(otherTilePos, m_RoomRows)].IsWalkable())
			{
				// Top side points
				tileBarrier.push_back(Point2f{ tile.GetBottomLeft().x, tile.GetBottomLeft().y + Tile::m_Side });
				tileBarrier.push_back(Point2f{ tile.GetBottomLeft().x + Tile::m_Side, tile.GetBottomLeft().y + Tile::m_Side });
			}
			otherTilePos.y = tilePos.y - 1;
			if (utils::GridPosValid(otherTilePos, m_RoomCols, m_RoomRows) && m_Tiles[utils::IndexFromGridPos(otherTilePos, m_RoomRows)].IsWalkable())
			{
				// bottom points
				tileBarrier.push_back(tile.GetBottomLeft());
				tileBarrier.push_back(Point2f{ tile.GetBottomLeft().x + Tile::m_Side, tile.GetBottomLeft().y });
			}

			if (tileBarrier.size() > 0)
			{
				m_Barriers.push_back(tileBarrier);
			}
		}
	}
}
std::vector<std::vector<Point2f>> Room::GetBarriers() const
{
	return m_Barriers;
}
GridPos Room::GetRoomPos() const
{
	return m_RoomPos;
}

bool Room::IsTopOpen() const
{
	return m_IsTopOpen;
}
bool Room::IsLeftOpen() const
{
	return m_IsLeftOpen;
}
bool Room::IsBottomOpen() const
{
	return m_IsBottomOpen;
}
bool Room::IsRightOpen() const
{
	return m_IsRightOpen;
}

void Room::SetConnection(bool shouldTopOpen, bool shouldLeftOpen, bool shouldBottomOpen, bool shouldRightOpen)
{
	m_IsTopOpen = shouldTopOpen;
	m_IsLeftOpen = shouldLeftOpen;
	m_IsBottomOpen = shouldBottomOpen;
	m_IsRightOpen = shouldRightOpen;
}
void Room::SetTopOpen(bool isOpen)
{
	m_IsTopOpen = isOpen;
}
void Room::SetLeftOpen(bool isOpen)
{
	m_IsLeftOpen = isOpen;
}
void Room::SetBottomOpen(bool isOpen)
{
	m_IsBottomOpen = isOpen;
}
void Room::SetRightOpen(bool isOpen)
{
	m_IsRightOpen = isOpen;
}
