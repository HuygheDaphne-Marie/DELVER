#pragma once
#include "Actor.h"
#include <vector>
#include "Animation.h"
#include "AnimatedTexture.h"

#include "SoundEffect.h"

class Pickup;
class Gun;

class Player final : public Actor
{
public: 
	enum class State
	{
		waiting,
		moving,
		firing,
		dead
	};

	Player(const Point2f& pos, int health, Gun* pGunEquiped = nullptr);
	~Player();

	//void Update(float elapsedSec, const Level& level) override;
	void Update(float elapsedSec, const Level& level, const Point2f mousePos);
	void Draw() const override;

	void EquipGun(Gun* pGunToEquip);
	void SwapGun(bool swappingToNext);
	Gun* GetEquippedGun() const;

	Controller* GetController() const;
	void SetController(Controller* controller);
	void SetState(const State& newstate);

	Pickup* GetPickup() const;
	void SetPickup(Pickup* pickup);

	bool IsDead() const;

	void GotHit();

	const int m_MaxHP;
	int m_CurrentHp;

private:
	State m_State;
	std::vector<Gun*> m_pGuns;
	size_t m_IdxEquippedGun;
	const Point2f m_StartPosition;
	Controller* m_pController;

	AnimatedTexture m_AnimatedTexture;
	Point2f m_LookPos;
	Pickup* m_pPickup;

	SoundEffect* m_pHurtSound;

	void UpdateTextureStateString();

	std::string GetStatePostfix() const;
};

