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
		floor,
		stairs
	};

	Tile(const GridPos& pos, Type tileType = Type::nothing);
	~Tile();

	GridPos GetTilePos() const;
	Type GetType() const;
	bool IsBarrier() const;
	Point2f GetBottomLeft() const;
	Texture* GetTexture() const;
	std::vector<Point2f> GetBarrier() const;

	void SetType(Type newType);
	void SetTexture(Texture* texture);

	void Draw() const;

private:
	const GridPos m_TilePos;
	Type m_Type;
	bool m_IsBarrier;
	Texture* m_pTexture;
};

