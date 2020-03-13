#pragma once
class Texture;

static const float m_Side;

class Tile
{
	enum class Type
	{
		nothing,
		wall,
		floor
	};

public:
	Tile(const GridPos& pos, Type tileType = Type::nothing);
	~Tile();

	GridPos GetTilePos() const;
	Type GetType() const;
	bool IsWalkable() const;

	void SetType(Type newType);

	void Draw() const;

private:
	const GridPos m_TilePos;
	Type m_Type;
	bool m_IsWalkable;
	Texture* m_pTexture;
};

