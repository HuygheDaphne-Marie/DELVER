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

	void SetLevelDimensions(int width, int height);

private:
	std::vector<Room*> m_Rooms;
	int m_LevelCols;
	int m_LevelRows;
	bool m_IsGenerated;

	void Generate();
	void GenerateStart(); // make start room which is open from all sides
	bool GenerateRoomAt(const GridPos& position); // returns false if there is already a room there
	void DestroyLevel(); // deletes all rooms
};

