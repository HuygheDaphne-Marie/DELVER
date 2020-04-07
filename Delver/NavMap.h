#pragma once
#include <vector>

class Level;

class NavMap
{
public:
	NavMap(const Level* level);
	~NavMap();

	void ReconstructNavMap(const Level* level);

	void Draw() const;

	const std::vector<bool>& GetNavMap() const;

private:
	std::vector<bool> m_NavMap;
	int m_Cols;
	int m_Rows;
};

