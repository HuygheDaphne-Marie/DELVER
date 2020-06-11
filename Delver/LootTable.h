#pragma once
#include "Enemy.h"
#include "Item.h"
#include "Pickup.h"
#include <vector>

class LootTable
{
public:
	LootTable(const Enemy::Type& relatedEnemy);
	~LootTable();

	std::vector<Item*> RollTable();

	const Enemy::Type m_RelatedEnemy;
private:
	struct TableEntry
	{
		Item* item;
		float dropChance;
		// might add more later
	};

	std::vector<TableEntry> m_Table;
	bool m_LoadSuccess;

	void LoadLootTable();
	void LoadTableEntries(const std::string& stringData);
};

