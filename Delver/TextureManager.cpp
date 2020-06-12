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
	//, m_PLAYER{ "Resources/Textures/Actors/player_temp.png" }
	//, m_BULLET{ "Resources/Textures/" }
	, m_FLOORS
	{
		"Resources/Textures/Level/floor_1.png",
		"Resources/Textures/Level/floor_2.png",
		"Resources/Textures/Level/floor_3.png",
		"Resources/Textures/Level/floor_4.png"
	}
#pragma region walls
	// Normal Segments
	, m_Wall_Single{ "Resources/Textures/Level/wall_single.png" }
	, m_Wall_Horizontal{ "Resources/Textures/Level/wall_horizontal.png" }
	, m_Wall_Vertical{ "Resources/Textures/Level/wall_vertical.png" }
	// Corners
	, m_Wall_Corner_Top_Right{ "Resources/Textures/Level/wall_corner_top_right.png" }
	, m_Wall_Corner_Top_Left{ "Resources/Textures/Level/wall_corner_top_left.png" }
	, m_Wall_Corner_Bottom_Right{ "Resources/Textures/Level/wall_corner_bottom_right.png" }
	, m_Wall_Corner_Bottom_Left{ "Resources/Textures/Level/wall_corner_bottom_left.png" }
	// Edge segments
	, m_Wall_Edge_Right{ "Resources/Textures/Level/wall_edge_right.png" }
	, m_Wall_Edge_Left{ "Resources/Textures/Level/wall_edge_left.png" }
	, m_Wall_Edge_Bottom{ "Resources/Textures/Level/wall_edge_bottom.png" }
	, m_Wall_Edge_Top{ "Resources/Textures/Level/wall_edge_top.png" }
	// Wall side
	, m_Wall_Side{ "Resources/Textures/Level/wall_side.png" }
#pragma endregion
#pragma region Items
	, m_Pickup_Bounce{ "Resources/Textures/Items/Bounce.png" }
	, m_Pickup_Warp{ "Resources/Textures/Items/warp.png" }
#pragma endregion

	, m_NO_TEXTURE{ "Resources/Textures/noTexture.png" }
{
	InitializeTextures();
}
TextureManager::~TextureManager()
{
	for (std::unordered_map<std::string, Texture*>::iterator itr{m_Textures.begin()}; itr != m_Textures.end(); itr++)
	{
		delete itr->second;
	}
	m_Textures.clear();
}

void TextureManager::InitializeTextures()
{
	m_Textures.insert({ m_NO_TEXTURE, new Texture{m_NO_TEXTURE} });

	//m_Textures[m_PLAYER] = new Texture{ m_PLAYER };

	for (const std::string& texture : m_FLOORS)
	{
		m_Textures.insert({ texture, new Texture{texture} });
	}
#pragma region walls
	// Normal Segments
	m_Textures.insert({ m_Wall_Horizontal, new Texture{m_Wall_Horizontal} });
	m_Textures.insert({ m_Wall_Vertical, new Texture{m_Wall_Vertical} });
	// Corners
	m_Textures.insert({ m_Wall_Corner_Top_Right, new Texture{m_Wall_Corner_Top_Right} });
	m_Textures.insert({ m_Wall_Corner_Top_Left, new Texture{m_Wall_Corner_Top_Left} });
	m_Textures.insert({ m_Wall_Corner_Bottom_Right, new Texture{m_Wall_Corner_Bottom_Right} });
	m_Textures.insert({ m_Wall_Corner_Bottom_Left, new Texture{m_Wall_Corner_Bottom_Left} });
	// Edge segments
	m_Textures.insert({ m_Wall_Edge_Right, new Texture{m_Wall_Edge_Right} });
	m_Textures.insert({ m_Wall_Edge_Left, new Texture{m_Wall_Edge_Left} });
	m_Textures.insert({ m_Wall_Edge_Bottom, new Texture{m_Wall_Edge_Bottom} });
	m_Textures.insert({ m_Wall_Edge_Top, new Texture{m_Wall_Edge_Top} });
	// Wall side
	m_Textures.insert({ m_Wall_Side, new Texture{m_Wall_Side} });
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
Texture* TextureManager::GetTexture(const std::string& textureName, bool tryget)
{
	auto pair{ m_Textures.find(textureName) };

	if (pair != m_Textures.end())
	{
		return pair->second;
	}
	else if(tryget)
	{
		Texture* newTexture{ new Texture(textureName) };
		if (newTexture->IsCreationOk())
		{
			m_Textures[textureName] = newTexture;
			return m_Textures[textureName];
		}
		else
		{
			delete newTexture;
		}
	}
	if (!tryget)
	{
		return nullptr;
	}
	return m_Textures.find(m_NO_TEXTURE)->second;
}

void TextureManager::AddTexture(const std::string& textureName, Texture* texture)
{
	if (texture == nullptr || m_Textures.find(textureName) != m_Textures.end())
	{
		return;
	}
	m_Textures.insert({ textureName, texture });
}