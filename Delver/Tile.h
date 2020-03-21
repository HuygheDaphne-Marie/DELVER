#pragma once
class Texture;



class Tile
{
public:
	static const float m_Side;
	enum class Type
	{
		nothing,
		wall,
		floor
	};

	Tile(const GridPos& pos, Type tileType = Type::nothing);
	~Tile();

	GridPos GetTilePos() const;
	Type GetType() const;
	bool IsWalkable() const;
	Point2f GetBottomLeft() const;

	void SetType(Type newType);

	void Draw() const;

private:
	const GridPos m_TilePos;
	Type m_Type;
	bool m_IsWalkable;
	Texture* m_pTexture;
};

