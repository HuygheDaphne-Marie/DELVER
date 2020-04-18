#pragma once
#include "BulletType.h"
#include "SpecialEffect.h"

class BulletManager;
class Texture;
class Actor;

class Gun
{
public:
	Gun(float recoilResist, float bulletSpeed, float fireRate, Texture* texture, 
		BulletType typeBullet, SpecialEffect::Type typeSpecial = SpecialEffect::Type::none);
	~Gun();

	void UpdateGun(float elapsedSec);
	void UpdateAimPos(const Point2f& aimPos);
	void UpdateGunPos(const Point2f& gunPos);

	const Actor* GetHolder() const;
	Point2f GetAimPos() const;
	Point2f GetGunPos() const;
	bool IsFiring() const;

	void SetHolder(Actor* holder);

	void StartFiring();
	void StopFiring();
	
	void Draw() const;

private:
	const float m_RecoilResist;
	const float m_BulletSpeed;
	const float m_FireRate;
	float m_TimeSinceLastShot;
	bool m_CanFire;
	bool m_IsFiring;

	BulletManager* m_pBulletManager;
	Texture* m_pGunTexture;
	Point2f m_AimPos;
	Point2f m_GunPos;
	Actor* m_pHolder;

	BulletType m_TypeOfBulletLoaded;
	SpecialEffect::Type m_TypeOfSpecialEffectLoaded;

	void Fire(float elapsedSec);
};

