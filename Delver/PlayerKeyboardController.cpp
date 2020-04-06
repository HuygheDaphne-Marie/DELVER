#include "pch.h"
#include "PlayerKeyboardController.h"
#include "Player.h"

PlayerKeyboardController::PlayerKeyboardController(Player* controlledPlayer)
	: m_pControlledPlayer{ controlledPlayer }
{
}
PlayerKeyboardController::~PlayerKeyboardController()
{
	m_pControlledPlayer = nullptr;
}

void PlayerKeyboardController::Update(float elapsedSec)
{

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_A])
	{
		m_pControlledPlayer->MoveLeft(elapsedSec);
		m_pControlledPlayer->SetState(Player::State::moving);
	}
	if (pStates[SDL_SCANCODE_D])
	{
		m_pControlledPlayer->MoveRight(elapsedSec);
		m_pControlledPlayer->SetState(Player::State::moving);
	}
	if (pStates[SDL_SCANCODE_W])
	{
		m_pControlledPlayer->MoveUp(elapsedSec);
		m_pControlledPlayer->SetState(Player::State::moving);
	}
	if (pStates[SDL_SCANCODE_S])
	{
		m_pControlledPlayer->MoveDown(elapsedSec);
		m_pControlledPlayer->SetState(Player::State::moving);
	}

}