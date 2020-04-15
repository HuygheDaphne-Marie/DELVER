#include "pch.h"
#include "AnimatedTexture.h"
#include "TextureManager.h"

AnimatedTexture::AnimatedTexture(const std::string& textureString)
	: m_SrcImg{ TextureManager::GetInstance()->GetTexture(textureString) }
	, m_SrcPath{ textureString }
	, m_Animations{}
	, m_CurrentState{"NO_STATE_YET"}
{
}
AnimatedTexture::~AnimatedTexture()
{
	//for (std::map<std::string, Animation>::iterator itr{m_Animations.begin()}; itr != m_Animations.end(); itr++)
	//{
	//	delete (*itr).second;
	//	(*itr).second = nullptr;
	//}
}

void AnimatedTexture::Draw(const Point2f& leftBottom) const
{
	const Animation* pCurAnimation{ GetAnimAnimationForCurrentState() };
	if (pCurAnimation != nullptr)
	{
		pCurAnimation->Draw(leftBottom);
	}
}
void AnimatedTexture::Draw(const Rectf& destRect) const
{
	const Animation* pCurAnimation{ GetAnimAnimationForCurrentState() };
	if (pCurAnimation != nullptr)
	{
		pCurAnimation->Draw(destRect);
	}
}
void AnimatedTexture::Update(float elapsedSec)
{
	Animation* pCurAnimation{ GetAnimAnimationForCurrentState() };
	if (pCurAnimation != nullptr)
	{
		pCurAnimation->Update(elapsedSec);
	}
}

void AnimatedTexture::AddState(const std::string stateString, const Animation& animation)
{
	Animation* pAnimation{ GetAnimAnimationForCurrentState() };
	if (pAnimation != nullptr)
	{
		delete pAnimation;
		pAnimation = nullptr;
	}
	m_Animations.insert({ stateString, animation });
}
void AnimatedTexture::SetState(const std::string newState)
{
	if (newState == m_CurrentState)
	{
		return;
	}

	Animation* pCurAnimation{ GetAnimAnimationForCurrentState() };
	if (pCurAnimation != nullptr)
	{
		pCurAnimation->ResetAnimation();
	}
	m_CurrentState = newState;
}
std::string AnimatedTexture::GetState() const
{
	return m_CurrentState;
}

std::string AnimatedTexture::ToXMLString() const
{
	std::string output{};
	output += "<AnimatedTexture>";
	output += "<SrcImgPath>" + m_SrcPath + "</SrcImgPath>";
	output += "<Animations>";
	for (std::map<std::string, Animation>::const_iterator itr{m_Animations.begin()}; itr != m_Animations.end(); itr++)
	{
		output += (*itr).second.ToXMLString();
	}
	output += "</Animations>";
	output += "</AnimatedTexture>";
}

Animation* AnimatedTexture::GetAnimAnimationForCurrentState()
{
	std::map<std::string, Animation>::iterator result{ m_Animations.find(m_CurrentState) };
	if (result != m_Animations.end())
	{
		return &(*result).second;
	}
	return nullptr;
}
const Animation* AnimatedTexture::GetAnimAnimationForCurrentState() const
{
	std::map<std::string, Animation>::const_iterator result{ m_Animations.find(m_CurrentState) };
	if (result != m_Animations.end())
	{
		return &(*result).second;
	}
	return nullptr;
}