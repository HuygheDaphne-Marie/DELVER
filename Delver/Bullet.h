#pragma once
#include "Vector2f.h"
#include "BulletType.h"

class Texture;
class SpecialEffect;
class Gun;
class Enemy;

class Bullet
{
public:
	Bullet(BulletType type);
	Bullet(const Bullet& other) = delete;
	Bullet& operator=(const Bullet& other) = delete;
	Bullet(Bullet&& other) = delete;
	Bullet& operator=(Bullet&& other) = delete;
	~Bullet();
	void SetType(const BulletType& type);
	void SetSpecialEffect(SpecialEffect* specialEffect);
	void SetPosition(const Point2f& position);
	void SetVelocity(const Vector2f& velocity);
	void SetTexture(Texture* texture);
	void SetFireOrigin(Gun* originGun);

	Point2f GetPosition() const;
	Vector2f GetVelocity() const;
	bool IsGoingToBeDestroyed() const;

	void Update(float elapsedSec, const std::vector<std::vector<Point2f>>& wallsVector);
	void Draw() const;

	void OnHit(Enemy* enemyHit);
	
	//bool CheckCollision(const Rectf& other) const;
	//bool HandleCollision(const Rectf& other) const;

private:
	Texture* m_pBulletTexture;
	Rectf m_Hitbox;
	BulletType m_Type;
	Vector2f m_Velocity;
	Point2f m_Position;
	SpecialEffect* m_pSpecialEffect;
	Gun* m_pGunWhichFired;

	bool m_IsGoingToBeDestroyed;
	
	bool CheckCollision(const std::vector<Point2f>& other, utils::HitInfo& hitInfo, float elapsedSec) const;
	void HandleCollision(const utils::HitInfo& hitInfo, float elapsedSec);
	//	- OnHit(--ref to thing hit--) : void
};

