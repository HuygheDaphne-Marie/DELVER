#pragma once
class Texture;

class Tile final
{
public:
	static const float m_Side;
	enum class Type
	{
		nothing,
		wall,
		wallSide,
		floor
	};

	Tile(const GridPos& pos, Type tileType = Type::nothing);
	~Tile();

	GridPos GetTilePos() const;
	Type GetType() const;
	bool IsWalkable() const;
	Point2f GetBottomLeft() const;

	void SetType(Type newType);
	void SetTexture(Texture* texture);

	void Draw() const;

private:
	const GridPos m_TilePos;
	Type m_Type;
	bool m_IsWalkable;
	Texture* m_pTexture;
};

