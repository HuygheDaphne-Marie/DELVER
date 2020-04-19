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
	SpecialEffect(const SpecialEffect& other) = delete;
	SpecialEffect& operator=(const SpecialEffect& other) = delete;
	SpecialEffect(SpecialEffect&& other) = delete;
	SpecialEffect& operator=(SpecialEffect&& other) = delete;
	virtual ~SpecialEffect();
	
	virtual void ApplySpecialEffect(Bullet* bullet, const utils::HitInfo& hitInfo, float elapsedSec) = 0;
	Type GetType() const;
	bool IsSpecialEffectDone() const;

protected:
	Type m_Type;
	bool m_IsSpecialEffectDone;
};

