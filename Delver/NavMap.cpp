#include "pch.h"
#include "NavMap.h"

#include "Level.h"
#include "Room.h"

NavMap::NavMap(const Level* level)
	: m_Cols{ 0 }
	, m_Rows{ 0 }
	, m_NavMap{ }
{
	if (level != nullptr)
	{
		ReconstructNavMap(level);
	}
}
NavMap::~NavMap()
{
}

void NavMap::ReconstructNavMap(const Level* level)
{
	m_Cols = level->GetLevelWidth() * Room::m_RoomCols;
	m_Rows = level->GetLevelHeight() * Room::m_RoomRows;

	m_NavMap = std::vector<bool>(m_Cols * m_Rows, false);
	for (const Room* room : level->GetAllRooms())
	{
		if (room != nullptr)
		{
			GridPos roomBottomLeft{ room->GetRoomPos() };
			roomBottomLeft.x *= Room::m_RoomCols;
			roomBottomLeft.y *= Room::m_RoomRows;
			room->MakeRoomNavMap(roomBottomLeft, m_NavMap, m_Cols);
		}
	}
}

void NavMap::Draw() const
{
	for (int i{ 0 }; i < m_NavMap.size(); i++)
	{
		if (m_NavMap[i])
		{
			glColor4f(0.f, 1.f, 0.f, 0.5f);
		}
		else
		{
			glColor4f(1.f, 0.f, 0.f, 0.5f);
		}

		const GridPos pos{ utils::GridPosFromIndex(i, m_Cols) };
		utils::FillRect(pos.x * Tile::m_Side, pos.y * Tile::m_Side, Tile::m_Side, Tile::m_Side);
	}
}

const std::vector<bool>& NavMap::GetNavMap() const
{
	return m_NavMap;
}