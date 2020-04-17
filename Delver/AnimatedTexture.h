#pragma once
#include "Animation.h"
#include "Texture.h"
#include <map>


class AnimatedTexture
{
public:
	const Texture* m_SrcImg;
	const std::string m_SrcPath;

	AnimatedTexture(const std::string& textureString);
	~AnimatedTexture();

	void Draw(const Point2f& leftBottom) const;
	void Draw(const Rectf& destRect) const;
	void Update(float elapsedSec);

	void AddState(const std::string stateString, const Animation& animation);
	void SetState(const std::string newState);
	std::string GetState() const;

	Animation* GetCurrentAnimation();
	const Animation* GetCurrentAnimation() const;

	std::string ToXMLString() const;
	void LoadAnimationsFromFile(const std::string& filePath);

private:
	std::map<std::string, Animation> m_Animations;
	std::string m_CurrentState;

	Animation* GetAnimAnimationForCurrentState();
	const Animation* GetAnimAnimationForCurrentState() const;

	void LoadAnimationsFromString(const std::string& entry);
	void ExtractAnimation(const std::string& animationEntry);
};

