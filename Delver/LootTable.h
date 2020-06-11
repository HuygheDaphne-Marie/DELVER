#pragma once
#include "Enemy.h"
#include "Item.h"
#include "Pickup.h"
#include <vector>
#include <unordered_map>

class LootTable
{
public:
	LootTable(const Enemy::Type& relatedEnemy);
	~LootTable();

	std::vector<Item*> RollTable();

	const Enemy::Type m_RelatedEnemy;
private:
	std::unordered_map<Item*, float> m_Table; // Item, chance to drop

	void LoadLootTable();
	void LoadTableEntries(const std::string& stringData);
};

