#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class Texture;

class TextureManager final
{
public:
	static const std::string PLAYER;
	static const std::string BULLET;

	static const std::vector<std::string> FLOORS;
	static const std::vector<std::string> WALLS;

	//static const std::string FLOOR_1; 
	//static const std::string FLOOR_2;
	//static const std::string FLOOR_3;
	//static const std::string FLOOR_4;
	//static const std::string WALL_1;
	//static const std::string WALL_2;

	TextureManager(const TextureManager& other) = delete;
	TextureManager& operator=(const TextureManager& other) = delete;
	TextureManager(TextureManager&& other) = delete;
	TextureManager& operator=(TextureManager&& other) = delete;
	~TextureManager();

	static TextureManager* GetInstance();

	Texture* GetTexture(const std::vector<std::string>& textureList) const;
	Texture* GetTexture(const std::string& textureName) const;

private:
	static const std::string NO_TEXTURE;
	std::unordered_map<std::string, Texture*> m_Textures;

	TextureManager();
	void InitializeTextures();
};

