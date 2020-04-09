#include "pch.h"
#include "Animation.h"
#include "TextureManager.h"
#include "Texture.h"

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

std::string Animation::ToXMLString()
{
	std::string output{ "<Animation>" };
	
	output += "<TexturePath>" + m_TexturePath + "</TexturePath>";
	output += "<Repeating>" + std::to_string(m_Repeating) + "</Repeating>";
	output += "<StartPos>" + std::to_string(m_StartPos.x) + "," + std::to_string(m_StartPos.y) + "</StartPos>";
	output += "<Width>" + std::to_string(m_Width) + "</Width>";
	output += "<Height>" + std::to_string(m_Height) + "</Height>";
	output += "<AmountOfFrames>" + std::to_string(m_AmountOfFrames) + "</m_AmountOfFrames>";
	output += "<FrameTime>" + std::to_string(m_FrameTime) + "</FrameTime>";

	output += "</Animation>";
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