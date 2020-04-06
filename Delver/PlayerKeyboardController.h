#pragma once
#include "Controller.h"

class Player;

class PlayerKeyboardController : public Controller
{
public:
	PlayerKeyboardController(Player* controlledPlayer);
	virtual ~PlayerKeyboardController();

	virtual void Update(float elapsedSec) override;

private:
	Player* m_pControlledPlayer;
};

