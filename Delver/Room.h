#pragma once
#include <vector>
#include "Tile.h"

static const int m_RoomCols{ 9 }; // Can change this to make rooms of different sizes
static const int m_RoomRows{ 9 };
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
	Room(const GridPos& position);
	~Room();
	void Generate();
	void Draw() const;
	std::vector<std::vector<Point2f>> GetBarriers() const;
	GridPos GetRoomPos() const;

	bool IsTopOpen() const;
	bool IsLeftOpen() const;
	bool IsBottomOpen() const;
	bool IsRightOpen() const;

	void SetConnection(bool shouldTopOpen, bool shouldLeftOpen, bool shouldBottomOpen, bool shouldRightOpen);
	void SetTopOpen(bool isOpen);
	void SetLeftOpen(bool isOpen);
	void SetBottomOpen(bool isOpen);
	void SetRightOpen(bool isOpen);

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

	std::vector<std::vector<Point2f>> m_Barriers;

	void GenerateEdges();
	void GenerateHallway(GridPos& hallwayStart, bool isHorizontal);
	void InitBarriers();
};

