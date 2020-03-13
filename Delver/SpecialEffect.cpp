#include "pch.h"
#include "SpecialEffect.h"

#include "Bullet.h"

SpecialEffect::SpecialEffect(Type type)
	: m_Type{ type }
	, m_IsSpecialEffectDone{ false }
{
}
SpecialEffect::~SpecialEffect()
{
}

SpecialEffect::Type SpecialEffect::GetType() const
{
	return m_Type;
}
bool SpecialEffect::IsSpecialEffectDone() const
{
	return	m_IsSpecialEffectDone;
}