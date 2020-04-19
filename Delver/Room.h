#pragma once
#include <vector>
#include "Tile.h"




class Room
{
	//enum class Connection
	//{
	//	all,
	//	top,
	//	left,
	//	bottom,
	//	right,
	//	topLeft,
	//	topBottom,
	//	topRight,
	//	leftBottom,
	//	leftRight,
	//	bottomRight
	//};

public:
	static const int m_RoomCols;
	static const int m_RoomRows;

	Room(const GridPos& position);
	Room(const Room& other) = delete;
	Room& operator=(const Room& other) = delete;
	Room(Room&& other) = delete;
	Room& operator=(Room&& other) = delete;
	~Room();
	void Generate();
	void Initialize();
	void Draw() const;
	std::vector<std::vector<Point2f>> GetBarriers() const;
	GridPos GetRoomPos() const;
	Point2f GetBottomLeft() const;

	bool IsTopOpen() const;
	bool IsLeftOpen() const;
	bool IsBottomOpen() const;
	bool IsRightOpen() const;

	void SetConnection(bool shouldTopOpen, bool shouldLeftOpen, bool shouldBottomOpen, bool shouldRightOpen);
	void SetTopOpen(bool isOpen);
	void SetLeftOpen(bool isOpen);
	void SetBottomOpen(bool isOpen);
	void SetRightOpen(bool isOpen);

	void MakeRoomNavMap(const GridPos& roomLeftBottom, std::vector<bool>& navMap, const int navMapCols) const; // could use a better name (ApplyRoomToNavMap??) idk yet

private:
	static const int m_HallwayWidth;

	const GridPos m_RoomPos;
	const Point2f m_BottomLeft;
	std::vector<Tile*> m_Tiles;
	//Connection m_Connection; // This is really a pain to set
	bool m_IsTopOpen;
	bool m_IsLeftOpen;
	bool m_IsBottomOpen;
	bool m_IsRightOpen;
	bool m_IsGenerated;

	std::vector<std::vector<Point2f>> m_Barriers;

	void GenerateEdges();
	void GenerateHallway(GridPos& hallwayStart, bool isHorizontal);

	void InitBarriers();

	Texture* GetWallTextureForTile(const Tile& tile) const;
	Texture* GetWallTextureForTile(bool topIsWall, bool bottomIsWall, bool leftIsWall, bool rightIsWall) const;
	bool CheckTileIsOfType(const GridPos& tilePos, const Tile::Type& type) const;
	bool CheckTileIsOneOfTypes(const GridPos& tilePos, const std::vector<Tile::Type>& types) const;

	void UpdateWallTexture(Tile& wallTile);

	void SetTile(const GridPos& pos, Tile::Type tileType);
	void UpdateNeighbourTiles(Tile& tile, Tile::Type oldType);

	Tile* GetTileAbove(const GridPos& pos);
	Tile* GetTileBelow(const GridPos& pos);
	Tile* GetTileRight(const GridPos& pos);
	Tile* GetTileLeft(const GridPos& pos);
};

