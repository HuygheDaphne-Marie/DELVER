#include "pch.h"
#include "AnimatedTexture.h"
#include "TextureManager.h"
#include <fstream>
#include <istream>
#include <sstream>


AnimatedTexture::AnimatedTexture(const std::string& textureString)
	: m_SrcImg{ TextureManager::GetInstance()->GetTexture(textureString) }
	, m_SrcPath{ textureString }
	, m_Animations{}
	, m_CurrentState{"NO_STATE_YET"}
{
	const std::string defaultSavePath{"Resources/Animations/"};

	size_t firstPos{ m_SrcPath.find_last_of('/') + 1 };
	size_t lastPos{ m_SrcPath.find_last_of('.') };
	if (firstPos != std::string::npos && lastPos != std::string::npos)
	{
		std::string defaultFilename{ m_SrcPath.substr(firstPos, lastPos - firstPos) + ".xml" };
		LoadAnimationsFromFile(defaultSavePath + defaultFilename);
	}
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

Animation* AnimatedTexture::GetCurrentAnimation()
{
	return GetAnimAnimationForCurrentState();
}
const Animation* AnimatedTexture::GetCurrentAnimation() const
{
	return GetAnimAnimationForCurrentState();
}

std::string AnimatedTexture::ToXMLString() const
{
	std::string output{};
	output += "<AnimatedTexture>\n";
	output += "<SrcImgPath>" + m_SrcPath + "</SrcImgPath>\n";
	output += "<Animations>\n";
	for (std::map<std::string, Animation>::const_iterator itr{m_Animations.begin()}; itr != m_Animations.end(); itr++)
	{
		output += "<AnimationEntry>\n";
		output += "<RepresentedState>" + (*itr).first + "</RepresentedState>\n";
		output += (*itr).second.ToXMLString();
		output += "</AnimationEntry>\n";
	}
	output += "</Animations>\n";
	output += "</AnimatedTexture>\n";

	return output;
}
void AnimatedTexture::LoadAnimationsFromFile(const std::string& filePath)
{
	std::ifstream ifs{ filePath };
	if (!ifs.good())
	{
		// file does not exist
		return;
	}

	bool hasFoundCorrectEntry{ false };
	std::string entry{};
	std::string line{};
	while (std::getline(ifs, line, '\n') || !hasFoundCorrectEntry)
	{
		entry += line;
		if (line == "</AnimatedTexture>")
		{
			const std::string firstSearch{ "<SrcImgPath>" };

			const size_t startPos{ entry.find(firstSearch) + firstSearch.size() };
			const size_t endPos{ entry.find("</SrcImgPath>") };

			if (startPos != std::string::npos && endPos != std::string::npos)
			{
				std::string entrySrcPath{ entry.substr(startPos, endPos - startPos) };

				if (entrySrcPath == m_SrcPath)
				{
					hasFoundCorrectEntry = true;
				}
			}

			if (!hasFoundCorrectEntry)
			{
				entry = "";
			}
		}
	}

	if (hasFoundCorrectEntry)
	{
		LoadAnimationsFromString(entry);
	}
}
void AnimatedTexture::LoadAnimationsFromString(const std::string& entry)
{
	std::string animations{ utils::GetAttributeValue("Animations", entry) };

	bool allAnimationsExtracted{ false };
	const std::string delimiter{ "</AnimationEntry>" };
	while (!allAnimationsExtracted)
	{
		std::string animationEntry{ utils::GetAttributeValue("AnimationEntry", animations) };
		if (animationEntry == "")
		{
			allAnimationsExtracted = true;
			break;
		}
		ExtractAnimation(animationEntry);

		if (!allAnimationsExtracted)
		{
			animations = animations.substr(animations.find(delimiter) + delimiter.size());
		}
	}

}
void AnimatedTexture::ExtractAnimation(const std::string& animationEntry)
{
	const std::string representedState{ utils::GetAttributeValue("RepresentedState", animationEntry) };
	Animation animation{ Animation::AnimationFromXML(utils::GetAttributeValue("Animation", animationEntry)) };
	AddState(representedState, animation);
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