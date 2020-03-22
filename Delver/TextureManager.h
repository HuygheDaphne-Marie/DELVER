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
	const std::vector<std::string> m_WALLS;

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

