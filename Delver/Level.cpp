#include "pch.h"
#include "Level.h"

#include "Room.h"

Level::Level(int width, int height)
	: m_Rooms{}
	, m_LevelCols{width}
	, m_LevelRows{height}
	, m_IsGenerated{false}
{
}
Level::~Level()
{
	DestroyLevel();
}

void Level::GenerateNextLevel()
{

}
void Level::Draw() const
{
	for (Room* room : m_Rooms)
	{
		if (room != nullptr)
		{
			room->Draw();
		}
	}
}

void Level::SetLevelDimensions(int width, int height)
{
	if (m_IsGenerated)
	{
		return;
	}

	m_LevelCols = width;
	m_LevelRows = height;
}

void Level::Generate()
{
	// Make empty level according to size
	for (int i{}; i < (m_LevelCols * m_LevelRows); i++)
	{
		m_Rooms.push_back(nullptr);
	}

	GenerateStart();
}
void Level::GenerateStart() // make start room which is open from all sides
{
	GridPos center{ m_LevelCols / 2, m_LevelRows / 2 };
	Room* centerRoom{ new Room(center) };
	m_Rooms[utils::IndexFromGridPos(center, m_RoomCols)] = centerRoom;
	centerRoom->SetConnection(true, true, true, true);
}
bool Level::GenerateRoomAt(const GridPos& position) // returns false if there is already a room there
{
	// check if there is already a room there, if so just close this connection. (or open the wall in that room)
	// check if we're trying to generate outside the level grid, if so then don't lmao
	
	return false;
}

void Level::DestroyLevel()
{
	if (!m_IsGenerated)
	{
		return;
	}

	for (Room* room : m_Rooms)
	{
		if (room != nullptr)
		{
			delete room;
			room = nullptr;
		}
	}
	m_IsGenerated = false;
}