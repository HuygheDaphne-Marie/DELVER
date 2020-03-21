#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"

const std::string TextureManager::NO_TEXTURE = "NO_TEXTURE";
const std::string TextureManager::PLAYER = "PLAYER";
const std::string TextureManager::FLOOR = "FLOOR";
const std::string TextureManager::WALL = "WALL";
const std::string TextureManager::BULLET = "BULLET";

TextureManager::TextureManager()
	: m_Textures{}
{
	InitializeTextures();
}
TextureManager::~TextureManager()
{
	for (std::unordered_map<std::string, Texture*>::value_type& value : m_Textures)
	{
		delete value.second;
		value.second = nullptr;
	}
}

void TextureManager::InitializeTextures()
{
	m_Textures.insert({ NO_TEXTURE, new Texture{"Resources/Textures/noTexture.png"} });
	//m_Textures.insert({ PLAYER, new Texture{""} });
	//m_Textures.insert({ FLOOR, new Texture{""} });
	//m_Textures.insert({ WALL, new Texture{""} });
	//m_Textures.insert({ BULLET, new Texture{""} });
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

Texture* TextureManager::GetTexture(const std::string& textureName) const
{
	auto pair{ m_Textures.find(textureName) };

	if (pair != m_Textures.end())
	{
		return pair->second;
	}
	return m_Textures.find(NO_TEXTURE)->second;
}