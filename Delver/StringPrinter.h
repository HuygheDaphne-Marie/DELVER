#pragma once

class Texture;

class StringPrinter
{
public:
	StringPrinter(const std::string& monospaceFontFile, int characterSize);
	~StringPrinter();

	void PrintString(const std::string& string, const Point2f& leftBottom) const;
private:
	Texture* m_pFontTexture;
	const std::string m_CharacterString;

	std::string GetFontTextureName(const std::string& monospaceFontFile, int characterSize);
	float GetCharOffset(char c) const;
};

