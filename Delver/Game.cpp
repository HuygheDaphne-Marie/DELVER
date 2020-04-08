#include "pch.h"
#include "Game.h"
#include "Room.h"

Game::Game( const Window& window )
	: m_Window{ window }
	, m_pBulletManager{ BulletManager::GetInstance() }
	, m_pTextureManager{ TextureManager::GetInstance() }
	, m_Player{ Point2f{window.width / 2, window.height / 2} }
	, m_TestEnemy{ Point2f{ 0, 0 }, 50.f, 1 }
	, m_MousePos{0, 0}
	, m_Camera{window.width, window.height}
	, m_Level{ 4, 4 }

{
	Initialize( );
}
Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	//TestBulletManager();
	m_Level.GenerateNextLevel();
	InitPlayer();
	m_Player.SetPosition(m_Level.GetPlayerSpawnPoint());

	m_TestEnemy.SetPosition(m_Level.GetPlayerSpawnPoint());
}
void Game::Cleanup( )
{
	delete m_pBulletManager;
	m_pBulletManager = nullptr;

	delete m_pTextureManager;
	m_pTextureManager = nullptr;
}

void Game::Update( float elapsedSec )
{
	m_pBulletManager->UpdateBullets(elapsedSec, m_Level);
	m_Player.Update(elapsedSec, m_Level, m_MousePos);

	m_TestEnemy.Update(elapsedSec, m_Level);

	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );

	glPushMatrix();
	m_Camera.Transform(m_Player.GetPosition());

	m_Level.Draw();

	m_TestEnemy.Draw();
	m_Player.Draw();

	m_pBulletManager->DrawBullets();

	// below should be moved to gun
	Gun* gun{ m_Player.GetEquippedGun() };
	glColor3f(1.f, 1.f, 1.f);
	utils::DrawLine(gun->GetAimPos(), gun->GetGunPos());
	// up should be moved to gun


	Room* playerRoom = m_Level.GetRoomAt(m_Player.GetPosition());
	if (playerRoom != nullptr)
	{
		std::vector<std::vector<Point2f>> walls = playerRoom->GetBarriers();
		for (std::vector<Point2f> wall : walls)
		{
			glColor3f(1.f, 0.f, 0.f);
			utils::DrawPolygon(wall);
		}
	}
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}
void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}

}
void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	m_MousePos.x = float(e.x);
	m_MousePos.y = m_Window.height - float(e.y);
	//m_pGun.UpdateAimPos(m_MousePos);
	
}
void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		//std::cout << " left button " << std::endl;
		m_Player.GetEquippedGun()->StartFiring();
		break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	}
}
void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		//std::cout << " left button " << std::endl;
		m_Player.GetEquippedGun()->StopFiring();
		break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

// Tests
void Game::TestBulletManager()
{
	Bullet* pSomeBullet = m_pBulletManager->GetBullet(BulletType::light, SpecialEffect::Type::warp);
	m_pBulletManager->QueueForDestroy(pSomeBullet);
	BulletManager* bm = BulletManager::GetInstance();
	pSomeBullet = bm->GetBullet(BulletType::medium);
	bm->QueueForDestroy(pSomeBullet);
}
void Game::InitPlayer()
{
	m_Player.EquipGun(new Gun(0.5f, 400.f, 0.05f, nullptr, BulletType::light, SpecialEffect::Type::bounce));
}