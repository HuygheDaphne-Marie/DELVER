#include "pch.h"
#include "LootTable.h"

#include <fstream>
#include <istream>
#include <sstream>

LootTable::LootTable(const Enemy::Type& relatedEnemy)
	: m_RelatedEnemy{relatedEnemy}
	, m_Table{}
	, m_LoadSuccess{false}
{
	LoadLootTable();
}
LootTable::~LootTable()
{
	for (TableEntry& entry : m_Table)
	{
		if (entry.item != nullptr)
		{
			delete entry.item;
			entry.item = nullptr;
		}
	}
	m_Table.clear();
}

std::vector<Item*> LootTable::RollTable()
{
	std::vector<Item*> droppedItems{};
	if (!m_LoadSuccess)
	{
		return droppedItems;
	}

	for (TableEntry entry : m_Table)
	{
		float rolledChance{ utils::GetRand(0, 100) / 1.f };
		if (rolledChance < entry.dropChance)
		{
			if (entry.item->m_ItemType == Item::ItemType::pickup)
			{
				Pickup* basePickup{ static_cast<Pickup*>(entry.item) };
				Pickup* tablePickup{ new Pickup(basePickup->GetPickupType(), basePickup->GetEffectDuration(), basePickup->m_Posistion, basePickup->m_Velocity) };
				droppedItems.push_back(tablePickup);
			}

		}
	}

	return droppedItems;
}

void LootTable::LoadLootTable()
{
	if (m_LoadSuccess)
	{
		return;
	}

	std::ifstream ifs{ "Resources/LootTables/" + std::to_string(int(m_RelatedEnemy)) + ".xml" };
	if (!ifs.good())
	{
		// file does not exist
		return;
	}

	std::string table{};
	std::string line{};
	while (std::getline(ifs, line, '\n'))
	{
		table += line;
	}

	LoadTableEntries(table);
}
void LootTable::LoadTableEntries(const std::string& stringData)
{
	std::string entries{ utils::GetAttributeValue("Entries", stringData) };

	bool allExtracted{ false };
	const std::string delimiter{ "</Entry>" };
	std::stringstream ss{};

	while (!allExtracted)
	{
		std::string entry{ utils::GetAttributeValue("Entry", entries) };
		if (entry == "")
		{
			allExtracted = true;
			break;
		}
		
		if (entry.find("Pickup") != std::string::npos)
		{
			Pickup* pickup{ new Pickup(entry) };
			float chance{};
			ss << utils::GetAttributeValue("Chance", entry);
			ss >> chance;
			ss.clear();

			m_Table.push_back(TableEntry{pickup, chance});
		}
		
		if (!allExtracted)
		{
			entries = entries.substr(entries.find(delimiter) + delimiter.size());
		}
	}

	m_LoadSuccess = true;
}