#pragma once
#include "Animation.h"

#include "Texture.h"
#include <vector>

class AnimatedTexture
{
public:
	const Texture* m_SrcImg;
	const std::string m_SrcPath;

	// TODO later, might not do it this way after all

private:
	std::vector<Animation> m_Animations;
};

