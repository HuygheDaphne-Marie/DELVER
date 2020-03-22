#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include "utils.h"

#include <iostream>

//const std::string NO_TEXTURE = "Resources/Textures/noTexture.png";
//const std::string PLAYER = "Resources/Textures/Actors/";
//const std::string BULLET = "Resources/Textures/";
//
//// Level Textures
//const std::vector<std::string> FLOORS
//{
//	"Resources/Textures/Level/floor_1.png",
//	"Resources/Textures/Level/floor_2.png",
//	"Resources/Textures/Level/floor_3.png",
//	"Resources/Textures/Level/floor_4.png"
//};
//
//const std::vector<std::string> WALLS
//{
//	"Resources/Textures/Level/wall_1.png",
//	"Resources/Textures/Level/wall_2.png"
//};

// ^^^^ These all give memory leaks and only thing I've found about them online is "Oh well not that bad" ^^^^
// It's because these statics are only destroyed after our check for memoryleaks I think

TextureManager::TextureManager()
	: m_Textures{}
	, m_PLAYER{ "Resources/Textures/Actors/" }
	, m_BULLET{ "Resources/Textures/" }
	, m_FLOORS
	{
		"Resources/Textures/Level/floor_1.png",
		"Resources/Textures/Level/floor_2.png",
		"Resources/Textures/Level/floor_3.png",
		"Resources/Textures/Level/floor_4.png"
	}
	, m_WALLS
	{
		"Resources/Textures/Level/wall_1.png",
		"Resources/Textures/Level/wall_2.png"
	}
	, m_NO_TEXTURE{ "Resources/Textures/noTexture.png" }
{
	InitializeTextures();
}
TextureManager::~TextureManager()
{
	for (std::unordered_map<std::string, Texture*>::iterator itr = m_Textures.begin(); itr != m_Textures.end(); itr++)
	{
		delete itr->second;
		itr->second = nullptr;
	}

	m_Textures.clear();
}

void TextureManager::InitializeTextures()
{
	m_Textures.insert({ m_NO_TEXTURE, new Texture{m_NO_TEXTURE} });

	////m_Textures.insert({ PLAYER, new Texture{""} });
	////m_Textures.insert({ BULLET, new Texture{""} });

	for (const std::string& texture : m_FLOORS)
	{
		m_Textures.insert({ texture, new Texture{texture} });
	}
	for (const std::string& texture : m_WALLS)
	{
		m_Textures.insert({ texture, new Texture{texture} });
	}
}

TextureManager* TextureManager::GetInstance()
{
	static TextureManager* instance;
	if (instance == nullptr)
	{
		instance = new TextureManager();
	}
	return instance;
}

Texture* TextureManager::GetTexture(const std::vector<std::string>& textureList) const
{
	return GetTexture(textureList[utils::GetRand(0, int(textureList.size() - 1))]);
}
Texture* TextureManager::GetTexture(const std::string& textureName) const
{
	auto pair{ m_Textures.find(textureName) };

	if (pair != m_Textures.end())
	{
		return pair->second;
	}
	return m_Textures.find(m_NO_TEXTURE)->second;
}