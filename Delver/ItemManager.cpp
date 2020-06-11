#include "pch.h"
#include "ItemManager.h"

#include "Item.h"
#include "Pickup.h"

ItemManager* ItemManager::GetInstance()
{
	static ItemManager* instance;
	if (instance == nullptr)
	{
		instance = new ItemManager();
	}
	return instance;
}

ItemManager::ItemManager()
	: m_Items{}
{
}
ItemManager::~ItemManager()
{
	for (Item* item : m_Items)
	{
		delete item;
		item = nullptr;
	}
}

void ItemManager::AddItem(Item* item)
{
	bool alreadyInList{false};
	for (Item* itemInList : m_Items)
	{
		if (itemInList == item)
		{
			alreadyInList = true;
		}
	}

	if (!alreadyInList)
	{
		m_Items.push_back(item);
	}
}

void ItemManager::QueueForDestroy(Item* item)
{
	m_ItemsToDelete.push_back(item);
}
void ItemManager::DestroyItems()
{
	for (Item* item : m_ItemsToDelete)
	{

		for (size_t idx{ 0 }; idx < m_Items.size(); idx++)
		{
			if (m_Items[idx] == item)
			{
				delete m_Items[idx];
				m_Items[idx] = m_Items[m_Items.size() - 1];
				idx--;
				m_Items.pop_back();
			}
		}

	}
	m_ItemsToDelete.clear();
}

void ItemManager::UpdateItems(float elapsedSec, Player& player)
{
	DestroyItems();
	for (Item* item : m_Items)
	{
		item->Update(elapsedSec, player);
	}
}
void ItemManager::DrawItems() const
{
	for (Item* item : m_Items)
	{
		item->Draw();
	}
}

size_t ItemManager::GetSize() const
{
	return m_Items.size();
}

void ItemManager::ClearAll()
{
	for (Item* item : m_Items)
	{
		delete item;
	}
	m_Items.clear();
}