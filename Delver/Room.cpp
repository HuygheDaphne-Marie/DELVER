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
	for (int i{}; i < m_RoomWidth * m_RoomHeight; i++)
	{
		GridPos tilePos{ GridPosFromIndex(i) };
		m_Tiles.push_back(Tile(tilePos, Tile::Type::floor));
	}

	GenerateEdges();

	m_IsGenerated = true;
}

void Room::Draw() const
{
	for (Tile tile : m_Tiles)
	{
		tile.Draw();
	}
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
	return GridPos{ index % m_RoomWidth, index / m_RoomHeight };
}
int Room::IndexFromGridPos(const GridPos& tilePos) const
{
	return tilePos.y * m_RoomWidth + tilePos.x;
}

void Room::GenerateEdges()
{

	for (int i{}; i < m_RoomWidth; i++)
	{
		m_Tiles[IndexFromGridPos(GridPos{ i, 0 })].SetType(Tile::Type::wall);
		m_Tiles[IndexFromGridPos(GridPos{ i, m_RoomHeight - 1 })].SetType(Tile::Type::wall);
		m_Tiles[IndexFromGridPos(GridPos{ 0, i })].SetType(Tile::Type::wall);
		m_Tiles[IndexFromGridPos(GridPos{ m_RoomWidth - 1, i })].SetType(Tile::Type::wall);
	}

	//if (m_IsTopOpen)
	//{

	//}
	//if (m_IsBottomOpen)
	//{
	//	
	//}

	//if (m_IsLeftOpen)
	//{

	//}
	//if (m_IsRightOpen)
	//{

	//}
}