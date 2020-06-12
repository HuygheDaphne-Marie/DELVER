#include "pch.h"
#include "StringPrinter.h"
#include "TextureManager.h"
#include "Texture.h"

//const std::string StringPrinter::m_CharacterString = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789: "; // These cause memory leaks for some reason

StringPrinter::StringPrinter(const std::string& monospaceFontFile, int characterSize)
	: m_pFontTexture{ nullptr }
	, m_CharacterString{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789: " }
	, m_CharacterWidth{}
{
	std::string textureName{ GetFontTextureName(monospaceFontFile, characterSize) };
	m_pFontTexture = TextureManager::GetInstance()->GetTexture(textureName, false);
	if (m_pFontTexture == nullptr)
	{
		m_pFontTexture = new Texture(m_CharacterString, monospaceFontFile, characterSize, Color4f{ 1,1,1,1 });
		TextureManager::GetInstance()->AddTexture(textureName, m_pFontTexture);
	}
	m_CharacterWidth = m_pFontTexture->GetWidth() / m_CharacterString.size();
}
StringPrinter::~StringPrinter()
{
	m_pFontTexture = nullptr;
}

void StringPrinter::PrintString(const std::string& string, const Point2f& leftBottom) const
{
	Rectf charRect{ 0, 0, m_CharacterWidth, m_pFontTexture->GetHeight() };
	Point2f drawPos{ leftBottom };

	for (char c : string)
	{
		charRect.left = GetCharOffset(c);
		m_pFontTexture->Draw(drawPos, charRect);
		drawPos.x += m_CharacterWidth;
	}
}

float StringPrinter::GetCharacterWidth() const
{
	return m_CharacterWidth;
}
float StringPrinter::GetCharacterHeight() const
{
	return m_pFontTexture->GetHeight();
}


std::string StringPrinter::GetFontTextureName(const std::string& monospaceFontFile, int characterSize)
{
	std::string beforeDot{ monospaceFontFile.substr(monospaceFontFile.find('.')) };
	return beforeDot + "_" + std::to_string(characterSize);
}
float StringPrinter::GetCharOffset(char c) const
{
	float offset{ 0 };
	for (char stringChar : m_CharacterString)
	{
		if (c == stringChar)
		{
			break;
		}
		offset += m_CharacterWidth;
	}
	return offset;
}