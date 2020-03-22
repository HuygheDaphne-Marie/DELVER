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
	const std::string m_Wall_Left_Right;
	const std::string m_Wall_Top_Bottom;
	// Wall top
	const std::string m_Top_Wall_Left_Right;
	// Wall corners
	const std::string m_Top_Wall_Corner;
	const std::string m_Wall_Bottom_Right;
	const std::string m_Wall_Bottom_Left;
	// Edge segments
	const std::string m_Wall_Left_Edge;
	const std::string m_Wall_Right_Edge;
	const std::string m_Wall_Top_Edge;
	const std::string m_Wall_Bottom_Edge;
#pragma endregion

	TextureManager(const TextureManager& other) = delete;
	TextureManager& operator=(const TextureManager& other) = delete;
	TextureManager(TextureManager&& other) = delete;
	TextureManager& operator=(TextureManager&& other) = delete;
	~TextureManager();

	static TextureManager* GetInstance();

	Texture* GetTexture(const std::vector<std::string>& textureList) const;
	Texture* GetTexture(const std::string& textureName) const;

private:
	const std::string m_NO_TEXTURE;
	std::unordered_map<std::string, Texture*> m_Textures;

	TextureManager();
	void InitializeTextures();
};

