#pragma once
#include <string>
class Texture;

class Animation final
{
public:
	const std::string m_TexturePath;
	const bool m_Repeating;
	const bool m_Reverse;

	const Point2f m_StartPos;
	const float m_Width;
	const float m_Height;
	
	const int m_AmountOfFrames;
	const float m_FrameTime;

	Animation(std::string texturePath, const Point2f& firstFrameBottomLeft, float width, float height, int amountOfFrames, float frameTime, bool repeating = true, bool reverse = false);
	Animation(std::string texturePath, int amountOfFrames, float frameTime, bool repeating = true, bool reverse = false);
	Animation(Texture* texture, const Point2f& firstFrameBottomLeft, float width, float height, int amountOfFrames, float frameTime, bool repeating = true, bool reverse = false);
	Animation(Texture* texture, int amountOfFrames, float frameTime, bool repeating = true, bool reverse = false);
	~Animation();

	void Update(float elapsedSec);
	void Draw(const Point2f& pos = Point2f{0, 0}) const;
	void Draw(const Rectf& destRect) const;

	void ResetAnimation();

	void SetCurrentFrame(int frame);
	int GetCurrentFrame() const;

	std::string ToXMLString();
	
private:
	int m_CurrentFrame;
	Rectf m_SrcRect;
	Texture* m_pAnimatedTexture;
	float m_AccuTime;

	void NextFrame();
};

