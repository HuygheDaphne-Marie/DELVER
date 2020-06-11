#include "pch.h"
#include "LootTable.h"

#include <fstream>
#include <istream>
#include <sstream>

LootTable::LootTable(const Enemy::Type& relatedEnemy)
	: m_RelatedEnemy{relatedEnemy}
	, m_Table{}
{
}
LootTable::~LootTable()
{
	for (std::unordered_map<Item*, float>::value_type& value : m_Table)
	{
		delete value.first;
	}
	m_Table.clear();
}

std::vector<Item*> LootTable::RollTable()
{
	std::vector<Item*> droppedItems{};

	for (std::unordered_map<Item*, float>::iterator itr{m_Table.begin()}; itr != m_Table.end(); itr++)
	{
		float rolledChance{ utils::GetRand(0, 100) / 100.f };
		if (rolledChance < (*itr).second)
		{
			if ((*itr).first->m_ItemType == Item::ItemType::pickup)
			{
				Pickup* tablePickup{ static_cast<Pickup*>((*itr).first) };
				droppedItems.push_back(new Pickup(*tablePickup));
			}
			
		}
	}

	return droppedItems;
}

void LootTable::LoadLootTable()
{
	std::ifstream ifs{ "lootTables/" + std::to_string(int(m_RelatedEnemy)) + ".xml" };
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
		std::string entry{ utils::GetAttributeValue("AnimationEntry", entries) };
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

			m_Table.insert({ pickup, chance });
		}
		
		if (!allExtracted)
		{
			entries = entries.substr(entries.find(delimiter) + delimiter.size());
		}
	}
}