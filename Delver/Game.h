#pragma once

#include "BulletManager.h"
#include "TextureManager.h"
#include "Gun.h"
#include "Player.h"
#include "Camera.h"
#include "Level.h"

#include <vector>

class Game
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	const Window m_Window;
	BulletManager* m_pBulletManager;
	TextureManager* m_pTextureManager;
	Player m_Player;

	Point2f m_MousePos;

	Camera m_Camera;
	Level m_Level;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void TestBulletManager();
	void InitPlayer();
};
