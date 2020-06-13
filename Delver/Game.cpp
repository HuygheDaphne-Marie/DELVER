#include "pch.h"
#include "Game.h"
#include "Room.h"

#include "LootDropper.h"
#include "Pickup.h"

#include "ResumeButton.h"
#include "FloorDisplay.h"
#include "PickupDisplay.h"
#include "HealthDisplay.h"
#include "RestartButton.h"

Game::Game( const Window& window )
	: m_Window{ window }
	, m_Player{ Point2f{window.width / 2, window.height / 2}, 5 }
	, m_MousePos{0, 0}
	, m_Camera{ window.width, window.height, 100.f, 100.f, Point2f{ 0, 0 } }
	, m_Level{ 4, 4, this }
	, m_pCrosshairTexture{nullptr}
	, m_IsPaused{false}
	, m_EnemyFactory{ &m_Player, &m_Level, {Enemy::Type::turret} }
	, m_Menu{}
{
	Initialize( );
}
Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pCrosshairTexture = TextureManager::GetInstance()->GetTexture("Resources/Textures/UI/Cursor_crosshair.png");
	SDL_ShowCursor(SDL_DISABLE);

	//TestBulletManager();
	m_Level.GenerateNextLevel();
	m_Camera.SetLevelBoundaries(m_Level.GetLevelBounds());
	
	InitPlayer();
	m_Player.SetPosition(m_Level.GetPlayerSpawnPoint());
	m_Camera.SetCenterPos(m_Player.GetPosition());

	EnemyManager::GetInstance()->m_pCurrentLevel = &m_Level;

	// TESTING
	//LootDropper ld{};
	//ld.DropLoot(Enemy::Type::turret, m_Player.GetPosition() + Vector2f{50.f, 10.f});

	// Menu Setup
#pragma region Menu Setup
	ResumeButton* resumeBtn{ new ResumeButton{this, Rectf{0, 0, 150, 50}, Color4f{0.5f, 0.5f, 0.5f, 1}} };
	FloorDisplay* floorDisplay{ new FloorDisplay(&m_Level, Point2f{10, 60}) };
	PickupDisplay* pickupDisplay{ new PickupDisplay(&m_Player, Point2f{ m_Window.width - PickupDisplay::m_CircleRadius, PickupDisplay::m_CircleRadius }) };
	HealthDisplay* healthDisplay{ new HealthDisplay(&m_Player, Point2f{20.f, 20.f}) };
	RestartButton* restartBtn{ new RestartButton(this, Rectf{m_Window.width / 2 - 75, m_Window.height / 2 - 25, 150, 50}, Color4f{0.5f, 0.5f, 0.5f, 1}) };

	m_Menu.AddComponent(Menu::State::paused, resumeBtn);
	m_Menu.AddComponent(Menu::State::playing, floorDisplay);
	m_Menu.AddComponent(Menu::State::playing, pickupDisplay);
	m_Menu.AddComponent(Menu::State::playing, healthDisplay);
	m_Menu.AddComponent(Menu::State::gameover, restartBtn);
#pragma endregion
}
void Game::Cleanup( )
{
	delete BulletManager::GetInstance();
	delete TextureManager::GetInstance();
	delete EnemyManager::GetInstance();
	delete ItemManager::GetInstance();
}

void Game::Update( float elapsedSec )
{
	m_Level.Update(m_Player.GetPosition());

	if (m_Player.IsDead() && m_Menu.m_MenuState != Menu::State::gameover)
	{	
		PauseGame();
		m_Menu.m_MenuState = Menu::State::gameover;
	}

	if (m_IsPaused)
	{
		return;
	}

	BulletManager::GetInstance()->UpdateBullets(elapsedSec, m_Level, m_Player);
	m_Player.Update(elapsedSec, m_Level, m_MousePos + m_Camera.GetClampDisplacement(m_Player.GetPosition()));

	EnemyManager::GetInstance()->UpdateEnemies(elapsedSec);
	ItemManager::GetInstance()->UpdateItems(elapsedSec, m_Player);

	m_Camera.UpdatePos(m_Player.GetPosition());
	m_Menu.Update(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );

	glPushMatrix();
	m_Camera.Transform();

	m_Level.Draw();

	ItemManager::GetInstance()->DrawItems();

	EnemyManager::GetInstance()->DrawEnemies();
	m_Player.Draw();

	BulletManager::GetInstance()->DrawBullets();

	Gun* gun{ m_Player.GetEquippedGun() };
	const float crosshairWidth{ m_pCrosshairTexture->GetWidth() };
	const float crosshairHeight{ m_pCrosshairTexture->GetWidth() };
	m_pCrosshairTexture->Draw(Rectf{ gun->GetAimPos().x - crosshairWidth, gun->GetAimPos().y - crosshairHeight, crosshairWidth * 2, crosshairHeight * 2 });

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

	m_Menu.Draw();
}

void Game::PauseGame()
{
	m_IsPaused = true;
	SDL_ShowCursor(SDL_ENABLE);
	m_Menu.m_MenuState = Menu::State::paused;
}
void Game::ResumeGame()
{
	m_IsPaused = false;
	SDL_ShowCursor(SDL_DISABLE);
	m_Menu.m_MenuState = Menu::State::playing;
}

void Game::HandleOldLevel()
{
	BulletManager::GetInstance()->ClearAll();
	EnemyManager::GetInstance()->ClearAll();
	ItemManager::GetInstance()->ClearAll();
}
void Game::HandleNewLevel()
{
	m_Player.SetPosition(m_Level.GetPlayerSpawnPoint());
	m_Camera.SetLevelBoundaries(m_Level.GetLevelBounds());
	m_Camera.SetCenterPos(m_Player.GetPosition());
}

EnemyFactory* Game::GetEnemyFactory()
{
	return &m_EnemyFactory;
}

void Game::ResetGame()
{
	HandleOldLevel();
	m_Level.Reset();
	m_Player.m_CurrentHp = m_Player.m_MaxHP;
	HandleNewLevel();
	ResumeGame();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}
void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_ESCAPE:
	case SDLK_p:
		PauseGame(); // temp
		break;
	case SDLK_r:
		ResumeGame(); // temp
		break;
	}
	m_Menu.OnPress(e);
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

	const Point2f clickPos{ float(e.x), m_Window.height - float(e.y) };
	m_Menu.OnClick(clickPos);
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

// Tests
void Game::TestBulletManager()
{
	Bullet* pSomeBullet = BulletManager::GetInstance()->GetBullet(BulletType::light, SpecialEffect::Type::warp);
	BulletManager::GetInstance()->QueueForDestroy(pSomeBullet);
	BulletManager* bm = BulletManager::GetInstance();
	pSomeBullet = bm->GetBullet(BulletType::medium);
	bm->QueueForDestroy(pSomeBullet);
}
void Game::InitPlayer()
{
	m_Player.EquipGun(new Gun(0.5f, 400.f, 0.05f, nullptr, BulletType::light, SpecialEffect::Type::bounce));
}