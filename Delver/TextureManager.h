#pragma once
#include <unordered_map>

class Texture;

class TextureManager final
{
public:
	static const std::string PLAYER;
	static const std::string FLOOR;
	static const std::string WALL;
	static const std::string BULLET;

	TextureManager(const TextureManager& other) = delete;
	TextureManager& operator=(const TextureManager& other) = delete;
	TextureManager(TextureManager&& other) = delete;
	TextureManager& operator=(TextureManager&& other) = delete;
	~TextureManager();

	static TextureManager* GetInstance();

	Texture* GetTexture(const std::string& textureName) const;

private:
	static const std::string NO_TEXTURE;
	std::unordered_map<std::string, Texture*> m_Textures;

	TextureManager();
	void InitializeTextures();
};

