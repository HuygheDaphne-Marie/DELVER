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
	DestroyLevel();
	Generate();
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

Room* Level::GetRoomAt(const GridPos& pos) const
{
	return m_Rooms[utils::IndexFromGridPos(pos, m_LevelCols)];
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

	Room* startRoom{ GenerateStart() };
	GenerateAdjacentRoomsOfRoom(startRoom);

	for (Room* room : m_Rooms)
	{
		if (room != nullptr)
		{
			room->Generate();
		}
	}
	m_IsGenerated = true;
}
Room* Level::GenerateStart() // make start room which is open from all sides
{
	GridPos center{ m_LevelCols / 2, m_LevelRows / 2 };
	Room* centerRoom{ new Room(center) };
	int idx = utils::IndexFromGridPos(center, m_LevelCols);
	m_Rooms[idx] = centerRoom;
	centerRoom->SetConnection(true, true, true, true);

	return centerRoom;
}
void Level::GenerateAdjacentRoomsOfRoom(Room* room)
{
	const GridPos roomPos{ room->GetRoomPos() };

	if (room->IsTopOpen())
	{
		GridPos newRoomPos{ roomPos.x, roomPos.y + 1 };
		GenerateRoomAt(newRoomPos, room);
	}
	if (room->IsLeftOpen())
	{
		GridPos newRoomPos{ roomPos.x - 1, roomPos.y };
		GenerateRoomAt(newRoomPos, room);
	}
	if (room->IsBottomOpen())
	{
		GridPos newRoomPos{ roomPos.x, roomPos.y - 1 };
		GenerateRoomAt(newRoomPos, room);
	}
	if (room->IsRightOpen())
	{
		GridPos newRoomPos{ roomPos.x + 1, roomPos.y };
		GenerateRoomAt(newRoomPos, room);
	}
}
void Level::ConnectRooms(Room* room1, Room* room2)
{
	if (room1->GetRoomPos().x == room2->GetRoomPos().x)
	{
		if (room1->GetRoomPos().y + 1 == room2->GetRoomPos().y)
		{
			room1->SetTopOpen(true);
			room2->SetBottomOpen(true);
		}
		else if (room1->GetRoomPos().y - 1 == room2->GetRoomPos().y)
		{
			room1->SetBottomOpen(true);
			room2->SetTopOpen(true);
		}
	}
	if (room1->GetRoomPos().y == room2->GetRoomPos().y)
	{
		if (room1->GetRoomPos().x + 1 == room2->GetRoomPos().x)
		{
			room1->SetRightOpen(true);
			room2->SetLeftOpen(true);
		}
		else if (room1->GetRoomPos().x - 1 == room2->GetRoomPos().x)
		{
			room1->SetLeftOpen(true);
			room2->SetRightOpen(true);
		}
	}
}
void Level::GenerateRoomAt(const GridPos& newRoomPos, Room* parentRoom) // returns false if there is already a room there
{
	// make sure not out of bounds
	if (newRoomPos.x < 0)
	{
		parentRoom->SetLeftOpen(false);
		return;
	}
	if (newRoomPos.x >= m_LevelCols)
	{
		parentRoom->SetRightOpen(false);
		return;
	}
	if (newRoomPos.y < 0)
	{
		parentRoom->SetBottomOpen(false);
		return;
	}
	if (newRoomPos.y >= m_LevelRows)
	{
		parentRoom->SetTopOpen(false);
		return;
	}

	// if there is room
	Room* roomAtNewRoomPos{ GetRoomAt(newRoomPos) };
	if (roomAtNewRoomPos != nullptr)
	{
		// open that's one side to parent's one
		ConnectRooms(parentRoom, roomAtNewRoomPos);
		return;
	}

	// otherwise just make the room 
	Room* newRoom{ new Room(newRoomPos) }; // TODO IMPORTANT: will need to generate some random connections at some point
	m_Rooms[utils::IndexFromGridPos(newRoomPos, m_LevelCols)] = newRoom;
	ConnectRooms(parentRoom, newRoom);

	// then make adjacent rooms for this one
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