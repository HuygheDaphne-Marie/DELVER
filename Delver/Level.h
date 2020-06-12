#pragma once
#include <vector>
#include "NavMap.h"

class Room;
class Game;

class Level
{
public:
	Level(int width = 0, int height = 0, Game* game = nullptr);
	// TODO: Rule of 5
	~Level();
	void GenerateNextLevel();
	void Update(const Point2f& playerPos);
	void Draw() const;

	const std::vector<Room*>& GetAllRooms() const;
	Room* GetRoomAt(const Point2f& pos) const;
	Room* GetRoomAt(const GridPos& pos) const;
	Point2f GetPlayerSpawnPoint() const;

	int GetLevelWidth() const;
	int GetLevelHeight() const;

	Rectf GetLevelBounds() const;

	void SetLevelDimensions(int width, int height);

	int GetCurrentLevel() const;

private:
	std::vector<Room*> m_Rooms;
	int m_LevelCols;
	int m_LevelRows;
	bool m_IsGenerated;

	Point2f m_PlayerSpawn;

	NavMap m_NavMap;
	Game* m_pGame;
	int m_CurrentLevel;

	void Generate();
	Room* GenerateStart(); // make start room which is open from all sides
	void GenerateAdjacentRoomsOfRoom(Room* room);
	void GenerateRoomAt(const GridPos& newRoomPos, Room* parentRoom); // returns false if there is already a room there
	void GenerateNewRoomOpenings(Room* room);
	
	void ConnectRooms(Room* room1, Room* room2);

	void DestroyLevel(); // deletes all rooms

	int GetRightmostRoomCol() const;
	int GetTopmostRoomRow() const;
	int GetLeftmostRoomCol() const;
	int GetBottommostRoomRow() const;

	void FindAndSetEndRoom();
	void SpawnEnemiesForRoom(const Room* room);
};

