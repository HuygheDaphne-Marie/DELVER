#pragma once

class Texture;

class StringPrinter
{
public:
	StringPrinter(const std::string& monospaceFontFile, int characterSize);
	~StringPrinter();

	void PrintString(const std::string& string, const Point2f& leftBottom) const;

	float GetCharacterWidth() const;
	float GetCharacterHeight() const;

private:
	Texture* m_pFontTexture;
	const std::string m_CharacterString;
	float m_CharacterWidth;

	std::string GetFontTextureName(const std::string& monospaceFontFile, int characterSize);
	float GetCharOffset(char c) const;
};

