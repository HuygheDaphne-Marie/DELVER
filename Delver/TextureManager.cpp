#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include "utils.h"

const std::string TextureManager::NO_TEXTURE = "Resources/Textures/noTexture.png";
const std::string TextureManager::PLAYER = "Resources/Textures/Actors/";
const std::string TextureManager::BULLET = "Resources/Textures/";

// Level Textures
const std::vector<std::string> TextureManager::FLOORS
{
	"Resources/Textures/Level/floor_1.png",
	"Resources/Textures/Level/floor_2.png",
	"Resources/Textures/Level/floor_3.png",
	"Resources/Textures/Level/floor_4.png"
};
//const std::string TextureManager::FLOOR_1 = "Resources/Textures/Level/floor_1.png";
//const std::string TextureManager::FLOOR_2 = "Resources/Textures/Level/floor_2.png";
//const std::string TextureManager::FLOOR_3 = "Resources/Textures/Level/floor_3.png";
//const std::string TextureManager::FLOOR_4 = "Resources/Textures/Level/floor_4.png";
const std::vector<std::string> TextureManager::WALLS
{
	"Resources/Textures/Level/wall_1.png",
	"Resources/Textures/Level/wall_2.png"
};
//const std::string TextureManager::WALL_1 = "Resources/Textures/Level/wall_1.png";
//const std::string TextureManager::WALL_2 = "Resources/Textures/Level/wall_2.png";



TextureManager::TextureManager()
	: m_Textures{}
{
	InitializeTextures();
}
TextureManager::~TextureManager()
{
	for (auto value : m_Textures)
	{
		delete value.second;
		value.second = nullptr;
	}
}

void TextureManager::InitializeTextures()
{
	m_Textures.insert({ NO_TEXTURE, new Texture{NO_TEXTURE} });

	//m_Textures.insert({ PLAYER, new Texture{""} });
	//m_Textures.insert({ BULLET, new Texture{""} });

	for (const std::string& texture : FLOORS)
	{
		m_Textures.insert({ texture, new Texture{texture} });
	}
	for (const std::string& texture : WALLS)
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
	return m_Textures.find(NO_TEXTURE)->second;
}