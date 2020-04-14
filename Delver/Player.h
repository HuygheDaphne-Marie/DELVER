#pragma once
#include "Actor.h"
#include <vector>
#include "Animation.h"

class Gun;

class Player final : public Actor
{
public: 
	enum class State
	{
		waiting,
		moving,
		dead
	};

	Player(const Point2f& pos, Gun* pGunEquiped = nullptr);
	~Player();

	//void Update(float elapsedSec, const Level& level) override;
	void Update(float elapsedSec, const Level& level, const Point2f mousePos, const Vector2f& CameraDisplacement);
	void Draw() const override;

	void EquipGun(Gun* pGunToEquip);
	void SwapGun(bool swappingToNext);
	Gun* GetEquippedGun() const;

	Controller* GetController() const;
	void SetController(Controller* controller);
	void SetState(const State& newstate);

private:
	State m_State;
	std::vector<Gun*> m_pGuns;
	size_t m_IdxEquippedGun;
	const Point2f m_StartPosition;
	Controller* m_pController;

	Animation m_WalkingUpAnimation;
};

