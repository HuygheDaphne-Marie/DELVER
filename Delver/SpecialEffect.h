#pragma once

class Bullet;

class SpecialEffect
{
public:
	enum class Type
	{
		none,
		bounce,
		warp,
		explosive // todo
	};

	SpecialEffect(Type type = Type::none);
	virtual ~SpecialEffect();
	
	virtual void ApplySpecialEffect(Bullet* bullet, const utils::HitInfo& hitInfo, float elapsedSec) = 0;
	Type GetType() const;
	bool IsSpecialEffectDone() const;

protected:
	Type m_Type;
	bool m_IsSpecialEffectDone;
};

