#include "pch.h"
#include "LootDropper.h"

const float LootDropper::m_DropSpeed = 50.f;

LootDropper::LootDropper()
	: m_pLootTables{}
{
}
LootDropper::~LootDropper()
{
	for (LootTable* pLt : m_pLootTables)
	{
		delete pLt;
	}
}

void LootDropper::DropLoot(const Enemy::Type& enemyType, Point2f deathPos)
{
	LootTable* enemyTable{ nullptr };

	for (LootTable* lt : m_pLootTables)
	{
		if (lt->m_RelatedEnemy == enemyType)
		{
			enemyTable = lt;
			break;
		}
	}

	if (enemyTable == nullptr)
	{
		enemyTable = LoadLootTable(enemyType);
	}

	if (enemyTable != nullptr)
	{
		std::vector<Item*> droppedItems{ enemyTable->RollTable() };
		for (Item* item : droppedItems)
		{
			item->m_Posistion = deathPos;
			item->m_SpawnPos = deathPos;
			GiveRandomVelocity(item);

			// add to item manager's list
		}
	}
}

LootTable* LootDropper::LoadLootTable(const Enemy::Type& enemyType)
{
	LootTable* table{ new LootTable(enemyType) };
	m_pLootTables.push_back(table);
	return table;
}
void LootDropper::GiveRandomVelocity(Item* drop)
{
	float x{ utils::GetRand(-100, 100) / 100.f };
	float y{ utils::GetRand(-100, 100) / 100.f };
	Vector2f velocity{ x, y };
	velocity = velocity.Normalized() * m_DropSpeed;
	drop->m_Velocity = velocity;
}