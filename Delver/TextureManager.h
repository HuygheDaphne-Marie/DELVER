#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class Texture;

class TextureManager final
{
public:
	const std::string m_PLAYER;
	const std::string m_BULLET;

	const std::vector<std::string> m_FLOORS;

#pragma region walls
	// Wall
	const std::string m_Wall_Single;
	const std::string m_Wall_Horizontal;
	const std::string m_Wall_Vertical;
	// Wall corners
	const std::string m_Wall_Corner_Top_Right;
	const std::string m_Wall_Corner_Top_Left;
	const std::string m_Wall_Corner_Bottom_Right;
	const std::string m_Wall_Corner_Bottom_Left;
	// Edge segments
	const std::string m_Wall_Edge_Right;
	const std::string m_Wall_Edge_Left;
	const std::string m_Wall_Edge_Bottom;
	const std::string m_Wall_Edge_Top;
	// Wall side
	const std::string m_Wall_Side;
#pragma endregion

	TextureManager(const TextureManager& other) = delete;
	TextureManager& operator=(const TextureManager& other) = delete;
	TextureManager(TextureManager&& other) = delete;
	TextureManager& operator=(TextureManager&& other) = delete;
	~TextureManager();

	static TextureManager* GetInstance();

	Texture* GetTexture(const std::vector<std::string>& textureList) const;
	Texture* GetTexture(const std::string& textureName) const;
	Texture* GetTexture(const std::string& textureName);

private:
	const std::string m_NO_TEXTURE;
	std::unordered_map<std::string, Texture*> m_Textures;

	TextureManager();
	void InitializeTextures();
};

