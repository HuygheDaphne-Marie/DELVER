#include "pch.h"
#include "LootDropper.h"

LootDropper::LootDropper()
	: m_LootTables{}
{
}

void LootDropper::DropLoot(const Enemy::Type& enemyType, Point2f deathPos)
{
	LootTable* enemyTable{ nullptr };

	for (LootTable lt : m_LootTables)
	{
		if (lt.m_RelatedEnemy == enemyType)
		{
			enemyTable = &lt;
			break;
		}
	}

	if (enemyTable == nullptr)
	{
		LoadLootTable(enemyType);
		std::vector<LootTable>::iterator itr{ m_LootTables.end()-- };
		for (LootTable lt : m_LootTables)
		{
			if (lt.m_RelatedEnemy == enemyType)
			{
				enemyTable = &lt;
				break;
			}
		}
	}

	if (enemyTable != nullptr)
	{
		std::vector<Item*> droppedItems{ enemyTable->RollTable() };
		for (Item* item : droppedItems)
		{
			// add to item manager's list
		}
	}
}

void LootDropper::LoadLootTable(const Enemy::Type& enemyType)
{
	m_LootTables.push_back(LootTable(enemyType));
}