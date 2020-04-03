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

Room* Level::GetRoomAt(const Point2f& pos) const
{
	const GridPos gridPosOfPoint{ int( pos.x / (Room::m_RoomCols * Tile::m_Side) ), int( pos.y / (Room::m_RoomRows * Tile::m_Side)) };

	if (utils::GridPosValid(gridPosOfPoint, m_LevelCols, m_LevelRows))
	{
		return m_Rooms[utils::IndexFromGridPos(gridPosOfPoint, m_LevelCols)];
	}
	return nullptr;
}
Room* Level::GetRoomAt(const GridPos& pos) const
{
	if (utils::GridPosValid(pos, m_LevelCols, m_LevelRows))
	{
		return m_Rooms[utils::IndexFromGridPos(pos, m_LevelCols)];
	}
	return nullptr;
}
Point2f Level::GetPlayerSpawnPoint() const
{
	return m_PlayerSpawn;
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

	m_PlayerSpawn = centerRoom->GetBottomLeft();
	m_PlayerSpawn.x += Room::m_RoomCols * Tile::m_Side / 2;
	m_PlayerSpawn.y += Room::m_RoomRows * Tile::m_Side / 2;

	return centerRoom;
}
void Level::GenerateAdjacentRoomsOfRoom(Room* room) // could do this when you try to connect but there is no room there, then you make it passing it's parent
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
	GenerateNewRoomOpenings(newRoom);
	GenerateAdjacentRoomsOfRoom(newRoom);
}
void Level::GenerateNewRoomOpenings(Room* room)
{
	int maxAmountOfNewOpenings{ utils::GetRand(0, 3) };
	const int chanceToGetNewOpening{ 50 }; // make this static const probably
	if (!room->IsTopOpen() && maxAmountOfNewOpenings > 0) // check if not parent or already generated
	{
		int chance{ utils::GetRand(0, 100) }; // make this function
		if (chance < chanceToGetNewOpening)
		{
			room->SetTopOpen(true);
			maxAmountOfNewOpenings--;
		}
	}
	if (!room->IsLeftOpen() && maxAmountOfNewOpenings > 0)
	{
		int chance{ utils::GetRand(0, 100) };
		if (chance < chanceToGetNewOpening)
		{
			room->SetLeftOpen(true);
			maxAmountOfNewOpenings--;
		}
	}
	if (!room->IsBottomOpen() && maxAmountOfNewOpenings > 0)
	{
		int chance{ utils::GetRand(0, 100) };
		if (chance < chanceToGetNewOpening)
		{
			room->SetBottomOpen(true);
			maxAmountOfNewOpenings--;
		}
	}
	if (!room->IsRightOpen() && maxAmountOfNewOpenings > 0)
	{
		int chance{ utils::GetRand(0, 100) };
		if (chance < chanceToGetNewOpening)
		{
			room->SetRightOpen(true);
			maxAmountOfNewOpenings--;
		}
	}
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