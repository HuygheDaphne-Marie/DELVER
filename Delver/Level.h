#pragma once
#include <vector>

class Room;

class Level
{
public:
	Level(int width = 0, int height = 0);
	~Level();
	void GenerateNextLevel();
	void Draw() const;

	Room* GetRoomAt(const Point2f& pos) const;
	Room* GetRoomAt(const GridPos& pos) const;

	void SetLevelDimensions(int width, int height);

private:
	std::vector<Room*> m_Rooms;
	int m_LevelCols;
	int m_LevelRows;
	bool m_IsGenerated;

	void Generate();
	Room* GenerateStart(); // make start room which is open from all sides
	void GenerateAdjacentRoomsOfRoom(Room* room);
	void ConnectRooms(Room* room1, Room* room2);
	void GenerateRoomAt(const GridPos& newRoomPos, Room* parentRoom); // returns false if there is already a room there
	void DestroyLevel(); // deletes all rooms
};

