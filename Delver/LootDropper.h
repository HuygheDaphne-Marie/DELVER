#pragma once
#include <vector>
#include "LootTable.h"
#include "Enemy.h"



class LootDropper
{
public:
	LootDropper();
	~LootDropper();

	void DropLoot(const Enemy::Type& enemyType, Point2f deathPos);

	static const float m_DropSpeed;
private:
	std::vector<LootTable*> m_pLootTables;

	LootTable* LoadLootTable(const Enemy::Type& enemyType);

	void GiveRandomVelocity(Item* drop);
};

