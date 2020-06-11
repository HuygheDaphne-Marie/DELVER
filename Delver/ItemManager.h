#pragma once

#include <vector>
#include "Player.h"
class Item;

class ItemManager
{
public:
	ItemManager(const ItemManager& other) = delete;
	ItemManager& operator=(const ItemManager& other) = delete;
	ItemManager(ItemManager&& other) = delete;
	ItemManager& operator=(ItemManager&& other) = delete;
	~ItemManager();

	static ItemManager* GetInstance();

	void AddItem(Item* item);

	void QueueForDestroy(Item* bullet);

	void UpdateItems(float elapsedSec, Player& player);
	void DrawItems() const;

	size_t GetSize() const;

	void ClearAll();

private:
	std::vector<Item*> m_Items;
	std::vector<Item*> m_ItemsToDelete;

	ItemManager();
	void DestroyItems();
};

