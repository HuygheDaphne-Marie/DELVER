#pragma once
#include "MenuComponent.h"
#include "Texture.h"

class VolumeBtn : public MenuComponent
{
public:
	VolumeBtn(const Rectf& btnRect, bool increaseBtn = true);
	VolumeBtn(const VolumeBtn& other) = delete;
	VolumeBtn& operator=(const VolumeBtn& other) = delete;
	VolumeBtn(VolumeBtn&& other) = delete;
	VolumeBtn& operator=(VolumeBtn&& other) = delete;
	virtual ~VolumeBtn();

	virtual void Update(float elapsedsec) override;
	virtual void Draw() const override;

	virtual void OnClick(const Point2f& clickPos) override;
	virtual void OnPress(const SDL_KeyboardEvent& e) override;

	static const int m_VolumeStep;

private:
	const Rectf m_BtnRect;
	Texture* m_pBtnTexture;
	bool m_IncreasesVolume;
};

