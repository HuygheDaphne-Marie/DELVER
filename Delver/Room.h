#pragma once
#include <vector>
#include "Tile.h"

static const int m_RoomCols{ 25 }; // Can change this to make rooms of different sizes
static const int m_RoomRows{ 21 };
static const int m_HallwayWidth{ 3 };

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
	Room(const GridPos& position, const Point2f& bottomLeft);
	~Room();
	void Generate();
	void Draw() const;
	std::vector<Point2f> GetBarriers() const;

	void SetConnection(bool shouldTopOpen, bool shouldLeftOpen, bool shouldBottomOpen, bool shouldRightOpen);

private:
	const GridPos m_RoomPos;
	const Point2f m_BottomLeft;
	std::vector<Tile> m_Tiles;
	//Connection m_Connection; // This is really a pain to set
	bool m_IsTopOpen;
	bool m_IsLeftOpen;
	bool m_IsBottomOpen;
	bool m_IsRightOpen;
	bool m_IsGenerated;

	GridPos GridPosFromIndex(int index) const;
	int IndexFromGridPos(const GridPos& tilePos) const;

	void GenerateEdges();
	void GenerateHallway(GridPos& hallwayStart, bool isHorizontal);
};

