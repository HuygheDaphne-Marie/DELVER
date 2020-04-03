#include "pch.h"
#include "Bullet.h"

#include "SpecialEffect.h"
#include "Texture.h"
#include "Gun.h"
#include "BulletManager.h"

Bullet::Bullet(BulletType type)
	: m_pBulletTexture{ nullptr }
	, m_Type{ type }
	, m_Velocity{0,0}
	, m_Position{0,0}
	, m_pSpecialEffect{nullptr}
	, m_GunWhichFired{nullptr}
	, m_IsGoingToBeDestroyed{ false }
{
}
Bullet::~Bullet()
{
	if (m_pSpecialEffect != nullptr)
	{
		switch (m_pSpecialEffect->GetType())
		{
		case SpecialEffect::Type::bounce:
		case SpecialEffect::Type::warp:
			delete m_pSpecialEffect;
			m_pSpecialEffect = nullptr;
			break;
		}
	}
}

void Bullet::SetType(const BulletType& type)
{
	m_Type = type;
}
void Bullet::SetSpecialEffect(SpecialEffect* specialEffect)
{
	m_pSpecialEffect = specialEffect;
}
void Bullet::SetPosition(const Point2f& position)
{
	m_Position = position;
}
void Bullet::SetVelocity(const Vector2f& velocity)
{
	m_Velocity = velocity;
}
void Bullet::SetTexture(Texture* texture)
{
	m_pBulletTexture = texture;
	m_Hitbox = Rectf{ 0,0, texture->GetWidth(), texture->GetHeight() };
}

Point2f Bullet::GetPosition() const
{
	return m_Position;
}
Vector2f Bullet::GetVelocity() const
{
	return m_Velocity;
}
bool Bullet::IsGoingToBeDestroyed() const
{
	return m_IsGoingToBeDestroyed;
}

void Bullet::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& wallsVector)
{
	bool hasHitAWall{ false };
	for (const std::vector<Point2f>& wall : wallsVector)
	{
		utils::HitInfo hitInfo{};
		if (CheckCollision(wall, hitInfo, elapsedSec)) // check if hit walls
		{
			HandleCollision(hitInfo, elapsedSec);
			hasHitAWall = true;
		}
	}
	if (!hasHitAWall)
	{
		m_Position += m_Velocity * elapsedSec;
	}

	// TODO: check colisions with non-walls and such
}
void Bullet::Draw() const
{
	// might need to get rotation and such first
	// probably most easy to translate
	// but best to store rotation & scale matricies in variables than recalculating each frame
	if (m_IsGoingToBeDestroyed)
	{
		return;
	}

	if (m_pBulletTexture != nullptr)
	{
		m_pBulletTexture->Draw();
	}
	else
	{
		glColor3f(1.f, 0.f, 0.f);
		utils::FillCircle(Circlef{ m_Position, 3.f });
	}
}

bool Bullet::CheckCollision(const std::vector<Point2f>& other, utils::HitInfo& hitInfo, float elapsedSec) const
{
	Point2f nextPos{ m_Position + m_Velocity * elapsedSec };
	bool res{ utils::Raycast(other, m_Position, nextPos, hitInfo) };
	return res;
}
void Bullet::HandleCollision(const utils::HitInfo& hitInfo, float elapsedSec)
{
	if (m_pSpecialEffect == nullptr || m_pSpecialEffect->GetType() == SpecialEffect::Type::none)
	{
		BulletManager::GetInstance()->QueueForDestroy(this);
		m_IsGoingToBeDestroyed = true;
	}
	else
	{
		m_pSpecialEffect->ApplySpecialEffect(this, hitInfo, elapsedSec);
		if (m_pSpecialEffect->IsSpecialEffectDone())
		{
			BulletManager::GetInstance()->QueueForDestroy(this);
			m_IsGoingToBeDestroyed = true;
		}
		// handle collison with wall for special bullets here 
			// - bounce will need to bounce
			// - time warp goes back 1sec
			// - explosive, well explodes...
	}
}