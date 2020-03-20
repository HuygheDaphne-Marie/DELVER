#include "pch.h"
#include "Gun.h"

#include "BulletManager.h"
#include "Texture.h"
#include "Bullet.h"

#include <iostream>

Gun::Gun(float recoilResist, float bulletSpeed, float fireRate, Texture* texture,
	BulletType typeBullet, SpecialEffect::Type typeSpecial)
	: m_RecoilResist{ recoilResist }
	, m_BulletSpeed{ bulletSpeed }
	, m_FireRate{ fireRate }
	, m_TimeSinceLastShot{ 0 }
	, m_CanFire{ true }
	, m_IsFiring{ false }
	, m_pBulletManager{ BulletManager::GetInstance() }
	, m_pGunTexture{ texture }
	, m_AimPos{ 0, 0 }
	, m_GunPos{ 0, 0 }
	, m_TypeOfBulletLoaded{ typeBullet }
	, m_TypeOfSpecialEffectLoaded{ typeSpecial }
{
}
Gun::~Gun()
{
}

void Gun::UpdateGun(float elapsedSec)
{
	if (!m_CanFire)
	{
		m_TimeSinceLastShot += elapsedSec;
		if (m_TimeSinceLastShot > m_FireRate)
		{
			m_CanFire = true;
			m_TimeSinceLastShot = 0;
		}
	}
	else if (m_IsFiring)
	{
		Fire();
	}
}
void Gun::UpdateAimPos(const Point2f& aimPos)
{
	m_AimPos = aimPos;
}
void Gun::UpdateGunPos(const Point2f& gunPos)
{
	m_GunPos = gunPos;
}

Point2f Gun::GetAimPos() const
{
	return m_AimPos;
}
Point2f Gun::GetGunPos() const
{
	return m_GunPos;
}

void Gun::StartFiring()
{
	m_IsFiring = true;
}
void Gun::StopFiring()
{
	m_IsFiring = false;
}
void Gun::Fire()
{
	if (!m_CanFire)
	{
		return;
	}

	Bullet* bulletToFire{ m_pBulletManager->GetBullet(m_TypeOfBulletLoaded, m_TypeOfSpecialEffectLoaded) };
	if (bulletToFire == nullptr) // no more specials left
	{
		m_TypeOfSpecialEffectLoaded = SpecialEffect::Type::none;
		bulletToFire = m_pBulletManager->GetBullet(m_TypeOfBulletLoaded);
		if (bulletToFire == nullptr) // no more bullets of that type left, don't fire
		{
			return;
		}
	}

	Vector2f trajectory{ Vector2f{m_GunPos, m_AimPos}.Normalized() };
	bulletToFire->SetVelocity(trajectory * m_BulletSpeed);
	bulletToFire->SetPosition(m_GunPos);
	m_CanFire = false;
	std::cout << "Bullets flying: " << m_pBulletManager->GetSize() << std::endl;

	// move player/enemy back (according to recoil)

}

void Gun::Draw() const
{
	glColor3f(0.f, 0.f, 1.f);
	utils::FillCircle(Circlef{ m_GunPos, 5.f });
}