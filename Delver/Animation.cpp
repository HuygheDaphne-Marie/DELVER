#include "pch.h"
#include "Animation.h"
#include "TextureManager.h"
#include "Texture.h"

#include <sstream>

Animation::Animation(std::string texturePath, const Point2f& firstFrameBottomLeft, float width, float height, int amountOfFrames, float frameTime, bool repeating, bool reverse)
	: m_TexturePath{ texturePath }
	, m_StartPos{ firstFrameBottomLeft }
	, m_Width{ width }
	, m_Height{ height }
	, m_AmountOfFrames{ amountOfFrames }
	, m_FrameTime{ frameTime }
	, m_Repeating{ repeating }
	, m_Reverse{ reverse }
	, m_AccuTime{ 0.f }
	, m_CurrentFrame{ 0 }
	, m_SrcRect{ firstFrameBottomLeft.x, firstFrameBottomLeft.y, width, height }
	, m_pAnimatedTexture{ TextureManager::GetInstance()->GetTexture(texturePath) }
{
}
Animation::Animation(std::string texturePath, int amountOfFrames, float frameTime, bool repeating, bool reverse)
	: m_TexturePath{ texturePath }
	, m_StartPos{ 0, 0 }
	, m_Width{ TextureManager::GetInstance()->GetTexture(texturePath)->GetWidth() / m_AmountOfFrames }
	, m_Height{ TextureManager::GetInstance()->GetTexture(texturePath)->GetHeight() }
	, m_AmountOfFrames{ amountOfFrames }
	, m_FrameTime{ frameTime }
	, m_Repeating{ repeating }
	, m_Reverse{ reverse }
	, m_AccuTime{ 0.f }
	, m_CurrentFrame{ 0 }
	, m_SrcRect{ 0, 0, 0, 0 }
	, m_pAnimatedTexture{ TextureManager::GetInstance()->GetTexture(texturePath) }
{
	m_SrcRect.width = m_Width;
	m_SrcRect.height = m_Height;
}
Animation::Animation(Texture* texture, const Point2f& firstFrameBottomLeft, float width, float height, int amountOfFrames, float frameTime, bool repeating, bool reverse)
	: m_TexturePath{ "None given" }
	, m_StartPos{ firstFrameBottomLeft }
	, m_Width{ width }
	, m_Height{ height }
	, m_AmountOfFrames{ amountOfFrames }
	, m_FrameTime{ frameTime }
	, m_Repeating{ repeating }
	, m_Reverse{ reverse }
	, m_AccuTime{ 0.f }
	, m_CurrentFrame{ 0 }
	, m_SrcRect{ firstFrameBottomLeft.x, firstFrameBottomLeft.y, width, height }
	, m_pAnimatedTexture{ texture }
{
}
Animation::Animation(Texture* texture, int amountOfFrames, float frameTime, bool repeating, bool reverse)
	: m_TexturePath{ "None given" }
	, m_StartPos{ 0, 0 }
	, m_Width{ texture->GetWidth() / m_AmountOfFrames }
	, m_Height{ texture->GetHeight() }
	, m_AmountOfFrames{ amountOfFrames }
	, m_FrameTime{ frameTime }
	, m_Repeating{ repeating }
	, m_Reverse{ reverse }
	, m_AccuTime{ 0.f }
	, m_CurrentFrame{ 0 }
	, m_SrcRect{ 0, 0, 0, 0 }
	, m_pAnimatedTexture{ texture }
{
}
Animation::~Animation()
{
	m_pAnimatedTexture = nullptr;
}

void Animation::Update(float elapsedSec)
{
	m_AccuTime += elapsedSec;
	if (m_AccuTime > m_FrameTime)
	{
		NextFrame();
		m_AccuTime -= m_FrameTime;
	}

}
void Animation::Draw(const Point2f& pos) const 
{
	m_pAnimatedTexture->Draw(pos, m_SrcRect);
}
void Animation::Draw(const Rectf& destRect) const
{
	m_pAnimatedTexture->Draw(destRect, m_SrcRect);
}

void Animation::ResetAnimation()
{
	//SetCurrentFrame(0);
	m_SrcRect.left = m_StartPos.x;
	m_SrcRect.bottom = m_StartPos.y;
	m_CurrentFrame = 0;
	m_AccuTime = 0;
}

void Animation::SetCurrentFrame(int frame)
{
	if (frame > m_AmountOfFrames || frame < 0)
	{
		return;
	}

	ResetAnimation();
	for (int i{}; i < frame; i++)
	{
		NextFrame();
	}

}
int Animation::GetCurrentFrame() const
{
	return m_CurrentFrame;
}

bool Animation::IsAnimationDone() const
{
	if (m_Repeating)
	{
		return false;
	}

	return m_CurrentFrame == m_AmountOfFrames;
}

std::string Animation::ToXMLString() const
{
	std::string output{ "<Animation>\n" };
	
	output += "<TexturePath>" + m_TexturePath + "</TexturePath>\n";
	output += "<Repeating>" + std::to_string(m_Repeating) + "</Repeating>\n";
	output += "<Reverse>" + std::to_string(m_Reverse) + "</Reverse>\n";
	output += "<StartPos>" + std::to_string(m_StartPos.x) + " " + std::to_string(m_StartPos.y) + "</StartPos>\n";
	output += "<Width>" + std::to_string(m_Width) + "</Width>\n";
	output += "<Height>" + std::to_string(m_Height) + "</Height>\n";
	output += "<AmountOfFrames>" + std::to_string(m_AmountOfFrames) + "</m_AmountOfFrames>\n";
	output += "<FrameTime>" + std::to_string(m_FrameTime) + "</FrameTime>\n";

	output += "</Animation>\n";
	return output;
}

void Animation::NextFrame()
{
	if (m_CurrentFrame == m_AmountOfFrames && !m_Repeating)
	{
		return;
	}

	if (m_CurrentFrame < m_AmountOfFrames)
	{
		m_CurrentFrame++;

		if (!m_Reverse)
		{
			m_SrcRect.left += m_Width;
			if (m_SrcRect.left >= m_pAnimatedTexture->GetWidth())
			{
				m_SrcRect.left = 0;
				m_SrcRect.bottom -= m_Height;
			}
		}
		else
		{
			m_SrcRect.left -= m_Width;
			if (m_SrcRect.left < -0.001f)
			{
				m_SrcRect.left = m_pAnimatedTexture->GetWidth();
				m_SrcRect.bottom -= m_Height;
			}
		}
	}

	if (m_CurrentFrame == m_AmountOfFrames && m_Repeating)
	{
		ResetAnimation();
	}
}

Animation Animation::AnimationFromXML(const std::string animationData)
{
	const std::string texturePath{ utils::GetAttributeValue("TexturePath", animationData) };
	
	const bool repeating{ utils::ToBool(utils::GetAttributeValue("Repeating", animationData)) };
	const bool reverse{ utils::ToBool(utils::GetAttributeValue("Reverse", animationData)) };

	const Point2f startLeftBottom{ utils::ToPoint2f(utils::GetAttributeValue("StartPos", animationData)) };

	std::stringstream ss{};

	ss << utils::GetAttributeValue("Width", animationData);
	float width{};
	ss >> width;
	ss.clear();

	ss << utils::GetAttributeValue("Height", animationData);
	float height{};
	ss >> height;
	ss.clear();

	ss << utils::GetAttributeValue("AmountOfFrames", animationData);
	int frameCount{};
	ss >> frameCount;
	ss.clear();

	ss << utils::GetAttributeValue("FrameTime", animationData);
	float timePerFrame{};
	ss >> timePerFrame;
	ss.clear();

	return Animation(texturePath, startLeftBottom, width, height, frameCount, timePerFrame, repeating, reverse);
}