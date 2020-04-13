#include "pch.h"
#include "BulletManager.h"

#include "Bullet.h"
#include "BounceEffect.h"
#include "WarpEffect.h"

#include "Room.h"


BulletManager* BulletManager::GetInstance()
{
	static BulletManager* instance;
	if (instance == nullptr)
	{
		instance = new BulletManager();
	}
	return instance;
}

BulletManager::BulletManager()
	: m_Bullets{}
{
}
BulletManager::~BulletManager()
{
	for (Bullet* bullet : m_Bullets)
	{
		delete bullet;
		bullet = nullptr;
	}
}

Bullet* BulletManager::GetBullet(const BulletType typeWanted, SpecialEffect::Type specialEffectWanted)
{
	Bullet* bullet{ new Bullet(typeWanted) };
	// make one special effect instance of each and pass a pointer, might need to make actual instances of some
	switch (specialEffectWanted)
	{
	case SpecialEffect::Type::bounce:
		bullet->SetSpecialEffect(new BounceEffect());
		break;
	case SpecialEffect::Type::warp:
		bullet->SetSpecialEffect(new WarpEffect());
		break;
	default:
		bullet->SetSpecialEffect(nullptr);
		break;
	}
	bullet->SetType(typeWanted);
	m_Bullets.push_back(bullet);
	return bullet;

	// Here the bullet manager could ask the inventory if there are any bullets like this left and if that is the case
	// then it makes one, otherwise returns nullptr
	// then gun would have to switch itself to just the type of bullet with no special effect
	// then ask again
	// if it has none then there are no bullets of that type left so it shouldn't be able to fire
}
void BulletManager::QueueForDestroy(Bullet* bullet)
{
	m_BulletsToDelete.push_back(bullet);
}
void BulletManager::DestroyBullets()
{
	for (Bullet* bullet : m_BulletsToDelete)
	{

		for (size_t idx{ 0 }; idx < m_Bullets.size(); idx++)
		{
			if (m_Bullets[idx] == bullet)
			{
				delete m_Bullets[idx];
				m_Bullets[idx] = m_Bullets[m_Bullets.size() - 1];
				idx--;
				m_Bullets.pop_back();
			}
		}

	}	
	m_BulletsToDelete.clear();
}

void BulletManager::UpdateBullets(float elapsedSec, const Level& currentLevel)
{
	DestroyBullets();
	for (Bullet* bullet : m_Bullets)
	{
		Point2f bulletPos{ bullet->GetPosition() };
		Room* roomAtPos{ currentLevel.GetRoomAt(bulletPos) };
		if (roomAtPos != nullptr)
		{
			bullet->Update(elapsedSec, roomAtPos->GetBarriers());
		}
		else
		{
			QueueForDestroy(bullet);
		}
	}
}
void BulletManager::DrawBullets() const
{
	for (Bullet* bullet : m_Bullets)
	{
		bullet->Draw();
	}
}

size_t BulletManager::GetSize() const
{
	return m_Bullets.size();
}