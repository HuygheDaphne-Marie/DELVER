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
#pragma region walls
	// Normal Segments
	, m_Wall_Left_Right{ "Resources/Textures/Level/wall_left_right.png" }
	, m_Wall_Top_Bottom{ "Resources/Textures/Level/wall_top_bottom.png" }

	// Top Segments
	, m_Top_Wall_Left_Right{ "Resources/Textures/Level/top_wall.png" }

	// Corners
	, m_Top_Wall_Corner{ "Resources/Textures/Level/wall_bottom.png" }
	, m_Wall_Bottom_Right{ "Resources/Textures/Level/wall_corner_bottom_right.png" }
	, m_Wall_Bottom_Left{ "Resources/Textures/Level/wall_corner_bottom_left.png" }

	// Edge segments
	, m_Wall_Left_Edge{ "Resources/Textures/Level/wall_left.png" }
	, m_Wall_Right_Edge{ "Resources/Textures/Level/wall_right.png" }
	, m_Wall_Top_Edge{ "Resources/Textures/Level/wall_top.png" }
	, m_Wall_Bottom_Edge{ "Resources/Textures/Level/wall_bottom.png" }
#pragma endregion
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

	for (const std::string& texture : m_FLOORS)
	{
		m_Textures.insert({ texture, new Texture{texture} });
	}
#pragma region walls
	m_Textures.insert({ m_Wall_Left_Right, new Texture{m_Wall_Left_Right} });
	m_Textures.insert({ m_Wall_Top_Bottom, new Texture{m_Wall_Top_Bottom} });

	m_Textures.insert({ m_Top_Wall_Left_Right, new Texture{m_Top_Wall_Left_Right} });

	m_Textures.insert({ m_Top_Wall_Corner, new Texture{m_Top_Wall_Corner} });
	m_Textures.insert({ m_Wall_Bottom_Right, new Texture{m_Wall_Bottom_Right} });
	m_Textures.insert({ m_Wall_Bottom_Left, new Texture{m_Wall_Bottom_Left} });

	m_Textures.insert({ m_Wall_Left_Edge, new Texture{m_Wall_Left_Edge} });
	m_Textures.insert({ m_Wall_Right_Edge, new Texture{m_Wall_Right_Edge} });
	m_Textures.insert({ m_Wall_Top_Edge, new Texture{m_Wall_Top_Edge} });
	m_Textures.insert({ m_Wall_Bottom_Edge, new Texture{m_Wall_Bottom_Edge} });
#pragma endregion
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