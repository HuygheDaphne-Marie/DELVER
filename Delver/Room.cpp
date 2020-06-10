#include "pch.h"
#include "Room.h"
#include "utils.h"
#include "TextureManager.h"

const int Room::m_RoomCols = 19;
const int Room::m_RoomRows = 19;
const int Room::m_HallwayWidth = 3;
const int Room::m_EdgeClearance = 5;

Room::Room(const GridPos& position)
	: m_RoomPos{position}
	, m_BottomLeft{ position.x * (m_RoomCols * Tile::m_Side), position.y * (m_RoomRows * Tile::m_Side) }
	, m_Tiles{m_RoomCols * m_RoomRows, nullptr}
	, m_IsTopOpen{false}
	, m_IsLeftOpen{false}
	, m_IsBottomOpen{false}
	, m_IsRightOpen{false}
	, m_IsGenerated{false}
	, m_HasPillars{false}
	, m_Barriers{}
	, m_Depth{-1}
	, m_IsEnd{false}
{
}
Room::~Room()
{
	for (Tile* tile : m_Tiles)
	{
		delete tile;
		tile = nullptr;
	}
}

void Room::Generate()
{
	for (int i{}; i < (m_RoomCols * m_RoomRows); i++)
	{
		GridPos tilePos{ utils::GridPosFromIndex(i, m_RoomCols) };
		m_Tiles[utils::IndexFromGridPos(tilePos, m_RoomCols)] = new Tile(tilePos);
		SetTile(tilePos, Tile::Type::floor);
	}

	GenerateEdges();
	if (m_HasPillars)
	{
		GeneratePillars();
	}
	if (m_IsEnd)
	{
		GridPos centerPos{ m_RoomCols / 2, m_RoomRows / 2 };
		SetTile(centerPos, Tile::Type::stairs);
		//m_Tiles[m_Tiles.size() / 2]->SetTexture(TextureManager::GetInstance()->GetTexture("pee pee poo poo"));
	}

	m_IsGenerated = true;
	Initialize();
}
void Room::Initialize()
{
	InitBarriers();
}

void Room::Draw() const
{
	if (!m_IsGenerated)
	{
		return;
	}

	glPushMatrix();
	glTranslatef(m_BottomLeft.x, m_BottomLeft.y, 0);
	for (Tile* tile : m_Tiles)
	{
		tile->Draw();
	}
	glPopMatrix();
}

std::vector<std::vector<Point2f>> Room::GetBarriers() const
{
	return m_Barriers;
}
GridPos Room::GetRoomPos() const
{
	return m_RoomPos;
}
Point2f Room::GetBottomLeft() const
{
	return Point2f{ m_RoomPos.x * m_RoomCols * Tile::m_Side, m_RoomPos.y * m_RoomRows * Tile::m_Side };
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

bool Room::GetHasPillars()
{
	return m_HasPillars;
}
void Room::SetHasPillars(bool newValue)
{
	if (!m_IsGenerated)
	{
		m_HasPillars = newValue;
	}
}

int Room::GetDepth()
{
	return m_Depth;
}
void Room::SetDepth(int depth)
{
	if (m_Depth == -1)
	{
		m_Depth = depth;
	}
}

bool Room::GetIsEnd()
{
	return m_IsEnd;
}
void Room::SetIsEnd(bool isEnd)
{
	if (!m_IsEnd)
	{
		m_IsEnd = isEnd;
	}
}

Tile* Room::GetTile(GridPos& pos)
{
	if (!utils::GridPosValid(pos, m_RoomCols, m_RoomRows))
	{
		return nullptr;
	}
	return m_Tiles[utils::IndexFromGridPos(pos, m_RoomCols)];
}

void Room::MakeRoomNavMap(const GridPos& roomLeftBottom, std::vector<bool>& navMap, const int navMapCols) const
{
	for (Tile* tile : m_Tiles)
	{
		navMap[utils::IndexFromGridPos((roomLeftBottom + tile->GetTilePos()), navMapCols)] = !tile->IsBarrier();
	}
}


// PRIVATE FUNCTIONS //
void Room::GenerateEdges()
{
	for (int i{}; i < m_RoomCols; i++)
	{
		SetTile(GridPos{ i, 0 }, Tile::Type::wall);
		SetTile(GridPos{ i, m_RoomRows - 1 }, Tile::Type::wall);
	}
	for (int i{}; i < m_RoomRows; i++)
	{
		SetTile(GridPos{ 0, i }, Tile::Type::wall);
		SetTile(GridPos{ m_RoomCols - 1, i }, Tile::Type::wall);
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
		SetTile(hallwayStart, Tile::Type::floor);
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

void Room::GeneratePillars()
{
	const int minPillars{0}, maxPillars{ int(m_Tiles.size() * 0.05f) };
	GeneratePillars(utils::GetRand(minPillars, maxPillars));
}
void Room::GeneratePillars(int AmountOfPillarsWanted)
{
	std::vector<GridPos> Posistions{};

	const int maxX{ m_RoomCols - m_EdgeClearance }, maxY{ m_RoomRows - m_EdgeClearance };
	for (int i{0}; i < AmountOfPillarsWanted; i++)
	{
		Posistions.push_back(GridPos{ utils::GetRand(m_EdgeClearance, maxX), utils::GetRand(m_EdgeClearance, maxY) });
	}
	GeneratePillars(Posistions);
}
void Room::GeneratePillars(std::vector<GridPos>& PillarPosistions)
{
	for(GridPos& PillarPos : PillarPosistions)
	{
		if (utils::GridPosValid(PillarPos, m_RoomCols, m_RoomRows))
		{
			SetTile(PillarPos, Tile::Type::wall);
		}
	}
}

void Room::InitBarriers()
{
	for (const Tile* tile : m_Tiles)
	{
		if (CheckTileIsOneOfTypes(tile->GetTilePos(), { Tile::Type::wall, Tile::Type::wallSide }))
		{
			std::vector<Point2f> tileBarrier{ tile->GetBarrier() };

			if (tileBarrier.size() > 0)
			{
				for (Point2f& point : tileBarrier)
				{
					point.x += m_BottomLeft.x;
					point.y += m_BottomLeft.y;
				}
				m_Barriers.push_back(tileBarrier);
			}
		}
	}
}

Texture* Room::GetWallTextureForTile(const Tile& tile) const
{
	const GridPos tilePos{ tile.GetTilePos() };
	bool topIsWall{ CheckTileIsOfType(GridPos{tilePos.x, tilePos.y + 1}, Tile::Type::wall) };
	bool bottomIsWall{ CheckTileIsOfType(GridPos{tilePos.x, tilePos.y - 1}, Tile::Type::wall) };
	bool leftIsWall{ CheckTileIsOfType(GridPos{tilePos.x - 1, tilePos.y}, Tile::Type::wall) };
	bool rightIsWall{ CheckTileIsOfType(GridPos{tilePos.x + 1, tilePos.y}, Tile::Type::wall) };

	return GetWallTextureForTile(topIsWall, bottomIsWall, leftIsWall, rightIsWall);
}
Texture* Room::GetWallTextureForTile(bool topIsWall, bool bottomIsWall, bool leftIsWall, bool rightIsWall) const
{
	if (!leftIsWall && !rightIsWall && !topIsWall && !bottomIsWall)
	{
		return TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Wall_Single);
	}
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

bool Room::CheckTileIsOfType(const GridPos& tilePos, const Tile::Type& type) const
{
	if (utils::GridPosValid(tilePos, m_RoomCols, m_RoomRows))
	{
		return m_Tiles[utils::IndexFromGridPos(tilePos, m_RoomCols)]->GetType() == type;
	}
	else
	{
		return false;
	}
}
bool Room::CheckTileIsOneOfTypes(const GridPos& tilePos, const std::vector<Tile::Type>& types) const
{
	bool isOneOfTypes{ false };
	for (const Tile::Type& type : types)
	{
		if (CheckTileIsOfType(tilePos, type))
		{
			isOneOfTypes = true;
		}
	}
	return isOneOfTypes;
}

void Room::UpdateWallTexture(Tile& wallTile)
{
	if (wallTile.GetType() != Tile::Type::wall)
	{
		return;
	}
	const GridPos tilePos{ wallTile.GetTilePos() };

	const GridPos TopPos{ tilePos.x, tilePos.y + 1 };
	const GridPos BottomPos{ tilePos.x, tilePos.y - 1 };
	const GridPos LeftPos{ tilePos.x - 1, tilePos.y };
	const GridPos RightPos{ tilePos.x + 1, tilePos.y };
	bool topIsWall{ CheckTileIsOfType(TopPos, Tile::Type::wall) };
	bool bottomIsWall{ CheckTileIsOfType(BottomPos, Tile::Type::wall) };
	bool leftIsWall{ CheckTileIsOfType(LeftPos, Tile::Type::wall) };
	bool rightIsWall{ CheckTileIsOfType(RightPos, Tile::Type::wall) };

	Texture* textureToChangeTo{ GetWallTextureForTile(topIsWall, bottomIsWall, leftIsWall, rightIsWall) };
	if (wallTile.GetTexture() == textureToChangeTo)
	{
		// We can assume that if it doesn't need to change, then it's neighbours are already correct
		// This will help not checking all walls if really only a limited amount need changing 
		return; 
	}
	wallTile.SetTexture(textureToChangeTo);

	if (topIsWall)
	{
		UpdateWallTexture(*m_Tiles[utils::IndexFromGridPos(TopPos, m_RoomCols)]);
	}
	if (bottomIsWall)
	{
		UpdateWallTexture(*m_Tiles[utils::IndexFromGridPos(BottomPos, m_RoomCols)]);
	}
	if (leftIsWall)
	{
		UpdateWallTexture(*m_Tiles[utils::IndexFromGridPos(LeftPos, m_RoomCols)]);
	}
	if (rightIsWall)
	{
		UpdateWallTexture(*m_Tiles[utils::IndexFromGridPos(RightPos, m_RoomCols)]);
	}
}

void Room::SetTile(const GridPos& pos, Tile::Type tileType)
{
	if (!utils::GridPosValid(pos, m_RoomCols, m_RoomRows))
	{
		return;
	}

	Tile* tile{ m_Tiles[utils::IndexFromGridPos(pos, m_RoomCols)] };
	if (tile->GetType() == tileType)
	{
		return;
	}

	Tile::Type oldType{ tile->GetType() };
	tile->SetType(tileType);

	switch (tile->GetType())
	{
	case Tile::Type::nothing:
		tile->SetTexture(nullptr);
		break;
	case Tile::Type::wall:
		UpdateWallTexture(*tile);
		break;
	case Tile::Type::wallSide:
		tile->SetTexture(TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Wall_Side));
		break;
	case Tile::Type::floor:
		tile->SetTexture(TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_FLOORS));
		break;
	case Tile::Type::stairs:
		tile->SetTexture(nullptr); //tile->SetTexture(TextureManager::GetInstance()->GetTexture(TextureManager::GetInstance()->m_Stairs));
		break;
	}
	UpdateNeighbourTiles(*tile, oldType);
}
void Room::UpdateNeighbourTiles(Tile& tile, Tile::Type oldType)
{
	if (oldType == Tile::Type::wall)
	{
		const GridPos& tilePos{ tile.GetTilePos() };
		Tile* tileTop{ GetTileAbove(tilePos) };
		if (tileTop != nullptr)
		{
			if (tileTop->GetType() == Tile::Type::wall)
			{
				UpdateWallTexture(*tileTop);
			}
		}

		Tile* tileLeft{ GetTileLeft(tilePos) };
		if (tileLeft != nullptr)
		{
			if (tileLeft->GetType() == Tile::Type::wall)
			{
				UpdateWallTexture(*tileLeft);
			}
		}

		Tile* tileRight{ GetTileRight(tilePos) };
		if (tileRight != nullptr)
		{
			if (tileRight->GetType() == Tile::Type::wall)
			{
				UpdateWallTexture(*tileRight);
			}
		}

		Tile* tileBelow{ GetTileBelow(tilePos) };
		if (tileBelow != nullptr)
		{
			if (tileBelow->GetType() == Tile::Type::wall)
			{
				UpdateWallTexture(*tileBelow);
			}

			if (tileBelow->GetType() != Tile::Type::wall)
			{
				SetTile(tileBelow->GetTilePos(), Tile::Type::floor);
			}
		}


	}
	if (tile.GetType() == Tile::Type::wall)
	{
		// make sure walls have sides under them
		Tile* tileBelow{ GetTileBelow(tile.GetTilePos()) };
		if (tileBelow != nullptr)
		{
			if (tileBelow->GetType() != Tile::Type::wall)
			{
				SetTile(tileBelow->GetTilePos(), Tile::Type::wallSide);
			}
		}
	}


	// if new is a floor and old above was wall make new above wallSide
	if (tile.GetType() != Tile::Type::wall && tile.GetType() != Tile::Type::wallSide)
	{
		GridPos pos{ tile.GetTilePos() };
		Tile* tileAbove{ GetTileAbove(pos) };
		if (tileAbove != nullptr && tileAbove->GetType() == Tile::Type::wall)
		{
			SetTile(tileAbove->GetTilePos(), Tile::Type::wallSide);
		}
	}
}

Tile* Room::GetTileAbove(const GridPos& pos)
{
	GridPos posAbove{ pos.x, pos.y + 1 };
	if (utils::GridPosValid(posAbove, m_RoomCols, m_RoomRows))
	{
		return m_Tiles[utils::IndexFromGridPos(posAbove, m_RoomCols)];
	}
	return nullptr;
}
Tile* Room::GetTileBelow(const GridPos& pos)
{
	GridPos posBelow{ pos.x, pos.y - 1 };
	if (utils::GridPosValid(posBelow, m_RoomCols, m_RoomRows))
	{
		return m_Tiles[utils::IndexFromGridPos(posBelow, m_RoomCols)];
	}
	return nullptr;
}
Tile* Room::GetTileRight(const GridPos& pos)
{
	GridPos posRight{ pos.x + 1, pos.y };
	if (utils::GridPosValid(posRight, m_RoomCols, m_RoomRows))
	{
		return m_Tiles[utils::IndexFromGridPos(posRight, m_RoomCols)];
	}
	return nullptr;
}
Tile* Room::GetTileLeft(const GridPos& pos)
{
	GridPos posLeft{ pos.x - 1, pos.y  };
	if (utils::GridPosValid(posLeft, m_RoomCols, m_RoomRows))
	{
		return m_Tiles[utils::IndexFromGridPos(posLeft, m_RoomCols)];
	}
	return nullptr;
}
