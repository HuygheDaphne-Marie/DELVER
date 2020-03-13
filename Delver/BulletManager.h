#pragma once
#include <vector>
#include "BulletType.h"
#include "SpecialEffect.h"

class Bullet;

class BulletManager final
{
public:
	BulletManager(const BulletManager& other) = delete;
	BulletManager& operator=(const BulletManager& other) = delete;
	BulletManager(BulletManager&& other) = delete;
	BulletManager& operator=(BulletManager&& other) = delete;
	~BulletManager();

	static BulletManager* GetInstance();

	Bullet* GetBullet(const BulletType typeWanted, SpecialEffect::Type specialEffectWanted = SpecialEffect::Type::none);
	void QueueForDestroy(Bullet* bullet);
	
	void UpdateBullets(float elapsedSec);
	void DrawBullets() const;

	size_t GetSize() const;

private:
	std::vector<Bullet*> m_Bullets;
	std::vector<Bullet*> m_BulletsToDelete;

	BulletManager();
	void DestroyBullets();
};

