#include "pch.h"
#include "Room.h"
#include "utils.h"
#include "TextureManager.h"

const int Room::m_RoomCols = 19;
const int Room::m_RoomRows = 19;
const int Room::m_HallwayWidth = 3;

Room::Room(const GridPos& position)
	: m_RoomPos{position}
	, m_BottomLeft{ position.x * (m_RoomCols * Tile::m_Side), position.y * (m_RoomRows * Tile::m_Side) }
	, m_Tiles{}
	, m_IsTopOpen{false}
	, m_IsLeftOpen{false}
	, m_IsBottomOpen{false}
	, m_IsRightOpen{false}
	, m_IsGenerated{false}
	, m_Barriers{}
{
}
Room::~Room()
{
}

void Room::Generate()
{
	for (int i{}; i < (m_RoomCols * m_RoomRows); i++)
	{
		GridPos tilePos{ utils::GridPosFromIndex(i, m_RoomCols) };
		m_Tiles.push_back(Tile(tilePos, Tile::Type::floor));
	}

	GenerateEdges();
	GenerateWallSides();

	m_IsGenerated = true;
	InitTiles();
	InitBarriers();
}
void Room::GenerateEdges()
{
	for (int i{}; i < m_RoomCols; i++)
	{
		m_Tiles[utils::IndexFromGridPos(GridPos{ i, 0 }, m_RoomCols)].SetType(Tile::Type::wall);
		m_Tiles[utils::IndexFromGridPos(GridPos{ i, m_RoomRows - 1 }, m_RoomCols)].SetType(Tile::Type::wall);
	}
	for (int i{}; i < m_RoomRows; i++)
	{
		m_Tiles[utils::IndexFromGridPos(GridPos{ 0, i }, m_RoomCols)].SetType(Tile::Type::wall);
		m_Tiles[utils::IndexFromGridPos(GridPos{ m_RoomCols - 1, i }, m_RoomCols)].SetType(Tile::Type::wall);
	}

	if (m_IsTopOpen)
	{
		GridPos hallwayTile{ (m_RoomCols - m_HallwayWidth + 1) / 2, m_RoomRows - 1 };
		GenerateHallway(hallwayTile, true);
	}
	if (m_IsBottomOpen)
	{
		GridPos hallwayTile{ (m_RoomCols - m_HallwayWidth + 1) / 2, 0 };
		GenerateHallway(hallwayTile, true);
	}

	if (m_IsLeftOpen)
	{
		GridPos hallwayTile{ 0, (m_RoomRows - m_HallwayWidth + 1) / 2 };
		GenerateHallway(hallwayTile, false);
	}
	if (m_IsRightOpen)
	{
		GridPos hallwayTile{ m_RoomCols - 1, (m_RoomRows - m_HallwayWidth + 1) / 2 };
		GenerateHallway(hallwayTile, false);
	}
}
void Room::GenerateHallway(GridPos& hallwayStart, bool isHorizontal)
{
	for (int i{}; i < m_HallwayWidth; i++)
	{
		m_Tiles[utils::IndexFromGridPos(hallwayStart, m_RoomCols)].SetType(Tile::Type::floor);
		if (isHorizontal)
		{
			hallwayStart.x++;
		}
		else
		{
			hallwayStart.y++;
		}
	}
}
void Room::GenerateWallSides()
{
	for (const Tile& tile : m_Tiles) // this will never apply to the first row, but it's nice to use a range
	{
		if (tile.GetType() == Tile::Type::wall)
		{
			GridPos tilePosBelow{ tile.GetTilePos() };
			tilePosBelow.y--;
			if (utils::GridPosValid(tilePosBelow, m_RoomCols, m_RoomRows))
			{
				Tile& tileBelow{ m_Tiles[utils::IndexFromGridPos(tilePosBelow, m_RoomCols)] };
				if (tileBelow.GetType() != Tile::Type::wall)
				{
					tileBelow.SetType(Tile::Type::wallSide);
					tileBelow.SetTexture(TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Wall_Side));
				}
			}
		}
	}
}

//void SetTile(Tile::Type tileType); would need an already made grid
//void UpdateWallTexture(Tile& wallTile);

void Room::Draw() const
{
	if (!m_IsGenerated)
	{
		return;
	}

	glPushMatrix();
	glTranslatef(m_BottomLeft.x, m_BottomLeft.y, 0);
	for (Tile tile : m_Tiles)
	{
		tile.Draw();
	}
	glPopMatrix();
}

Texture* Room::GetWallTextureForTile(const Tile& tile)
{
	GridPos tilePos{ tile.GetTilePos() };
	bool topIsWall{ CheckIfTileIsOfType(GridPos{tilePos.x, tilePos.y + 1}, Tile::Type::wall) };
	bool bottomIsWall{ CheckIfTileIsOfType(GridPos{tilePos.x, tilePos.y - 1}, Tile::Type::wall) };
	bool leftIsWall{ CheckIfTileIsOfType(GridPos{tilePos.x - 1, tilePos.y}, Tile::Type::wall) };
	bool rightIsWall{ CheckIfTileIsOfType(GridPos{tilePos.x + 1, tilePos.y}, Tile::Type::wall) };

#pragma region wall_segments
	if (leftIsWall && rightIsWall)
	{
		return TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Wall_Horizontal);
	}
	if (topIsWall && bottomIsWall) // side of the room
	{
		return TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Wall_Vertical);
	}
#pragma endregion
#pragma region corners
	if (topIsWall && rightIsWall) // bottom left corner
	{
		return TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Wall_Corner_Bottom_Left);
	}
	if (topIsWall && leftIsWall) // bottom right corner
	{
		return TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Wall_Corner_Bottom_Right);
	}

	if (bottomIsWall && rightIsWall) // top left corner
	{
		return TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Wall_Corner_Top_Left);
	}
	if (bottomIsWall && leftIsWall) // top right corner
	{
		return TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Wall_Corner_Top_Right);
	}
#pragma endregion
#pragma region wall_ends
	if (topIsWall) // bottom edge
	{
		return TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Wall_Edge_Bottom);
	}
	if (bottomIsWall) // top edge
	{
		return TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Wall_Edge_Top);
	}

	if (rightIsWall) // left edge
	{
		return TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Wall_Edge_Left);
	}
	if (leftIsWall) // right edge
	{
		return TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Wall_Edge_Right);
	}
#pragma endregion

	return TextureManager::GetInstance()->GetTexture("this will not give any texture");
}
void Room::InitTiles()
{
	for (Tile& tile : m_Tiles)
	{
		switch (tile.GetType())
		{
		case Tile::Type::nothing:
			tile.SetTexture(nullptr);
			break;
		case Tile::Type::floor:
			tile.SetTexture(TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_FLOORS));
			break;
		case Tile::Type::wall:
			tile.SetTexture(GetWallTextureForTile(tile));
			break;
		}
	}
}
void Room::InitBarriers()
{
	for (const Tile& tile : m_Tiles)
	{
		if (!tile.IsWalkable())
		{
			std::vector<Point2f> tileBarrier{};
			GridPos tilePos{ tile.GetTilePos() };
			GridPos otherTilePos{ tilePos.x + 1, tilePos.y };
			Point2f bottomLeft{ tile.GetBottomLeft() };
			
			bottomLeft.x += m_BottomLeft.x;
			bottomLeft.y += m_BottomLeft.y;
			
			//// Left & right
			if (utils::GridPosValid(otherTilePos, m_RoomCols, m_RoomRows) && m_Tiles[utils::IndexFromGridPos(otherTilePos, m_RoomCols)].IsWalkable())
			{
				// Barrier on right side
				tileBarrier.push_back(Point2f{ bottomLeft.x + Tile::m_Side, bottomLeft.y });
				tileBarrier.push_back(Point2f{ bottomLeft.x + Tile::m_Side, bottomLeft.y + Tile::m_Side });
			}
			otherTilePos.x = tilePos.x - 1;
			if (utils::GridPosValid(otherTilePos, m_RoomCols, m_RoomRows) && m_Tiles[utils::IndexFromGridPos(otherTilePos, m_RoomCols)].IsWalkable())
			{
				// Barrier on left side
				tileBarrier.push_back(Point2f{ bottomLeft.x, bottomLeft.y });
				tileBarrier.push_back(Point2f{ bottomLeft.x, bottomLeft.y + Tile::m_Side });
			}

			otherTilePos.x = tilePos.x;

			// Top & bottom
			otherTilePos.y = tilePos.y + 1;
			if (utils::GridPosValid(otherTilePos, m_RoomCols, m_RoomRows) && m_Tiles[utils::IndexFromGridPos(otherTilePos, m_RoomCols)].IsWalkable())
			{
				// Top side points
				tileBarrier.push_back(Point2f{ bottomLeft.x, bottomLeft.y + Tile::m_Side });
				tileBarrier.push_back(Point2f{ bottomLeft.x + Tile::m_Side, bottomLeft.y + Tile::m_Side });
			}
			otherTilePos.y = tilePos.y - 1;
			if (utils::GridPosValid(otherTilePos, m_RoomCols, m_RoomRows) && m_Tiles[utils::IndexFromGridPos(otherTilePos, m_RoomCols)].IsWalkable())
			{
				// bottom points
				tileBarrier.push_back(Point2f{ bottomLeft.x, bottomLeft.y });
				tileBarrier.push_back(Point2f{ bottomLeft.x + Tile::m_Side, bottomLeft.y });
			}

			if (tileBarrier.size() > 0)
			{
				m_Barriers.push_back(tileBarrier);
			}
		}
	}
}
std::vector<std::vector<Point2f>> Room::GetBarriers() const
{
	return m_Barriers;
}
GridPos Room::GetRoomPos() const
{
	return m_RoomPos;
}

bool Room::IsTopOpen() const
{
	return m_IsTopOpen;
}
bool Room::IsLeftOpen() const
{
	return m_IsLeftOpen;
}
bool Room::IsBottomOpen() const
{
	return m_IsBottomOpen;
}
bool Room::IsRightOpen() const
{
	return m_IsRightOpen;
}

void Room::SetConnection(bool shouldTopOpen, bool shouldLeftOpen, bool shouldBottomOpen, bool shouldRightOpen)
{
	m_IsTopOpen = shouldTopOpen;
	m_IsLeftOpen = shouldLeftOpen;
	m_IsBottomOpen = shouldBottomOpen;
	m_IsRightOpen = shouldRightOpen;
}
void Room::SetTopOpen(bool isOpen)
{
	m_IsTopOpen = isOpen;
}
void Room::SetLeftOpen(bool isOpen)
{
	m_IsLeftOpen = isOpen;
}
void Room::SetBottomOpen(bool isOpen)
{
	m_IsBottomOpen = isOpen;
}
void Room::SetRightOpen(bool isOpen)
{
	m_IsRightOpen = isOpen;
}

bool Room::CheckIfTileIsOfType(const GridPos& tilePos, const Tile::Type& type)
{
	if (utils::GridPosValid(tilePos, m_RoomCols, m_RoomRows))
	{
		return m_Tiles[utils::IndexFromGridPos(tilePos, m_RoomCols)].GetType() == type;
	}
	else
	{
		return false;
	}
}
