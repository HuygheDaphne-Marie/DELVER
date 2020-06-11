#pragma once
#include <vector>
#include "LootTable.h"
#include "Enemy.h"

class LootDropper
{
public:
	LootDropper();

	void DropLoot(const Enemy::Type& enemyType, Point2f deathPos);

private:
	std::vector<LootTable> m_LootTables;

	void LoadLootTable(const Enemy::Type& enemyType);
};

