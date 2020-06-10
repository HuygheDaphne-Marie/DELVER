#include "pch.h"
#include "EnemyFactory.h"
#include "TurretBehaviour.h"
#include "TurretDrawing.h"
#include "Player.h"
#include "Level.h"
#include "Gun.h"

EnemyFactory::EnemyFactory(Player* player, Level* level, const std::initializer_list<Enemy::Type> allowedTypes)
	: m_pPlayer{ player }
	, m_pLevel{ level }
	, m_RandomSpawnableEnemyTypes { allowedTypes }
{
}

void EnemyFactory::AllowRandomCreationOfType(Enemy::Type type)
{
	m_RandomSpawnableEnemyTypes.insert(type);
}
void EnemyFactory::DisallowRandomCreationOfType(Enemy::Type type)
{
	m_RandomSpawnableEnemyTypes.erase(type);
}

Enemy* EnemyFactory::CreateEnemyOfType(Enemy::Type type, const Point2f& pos)
{
	switch (type)
	{
	case Enemy::Type::turret:
	{
		Actor::ActorData actorData{ pos, Actor::Dimension{48.f, 48.f, Rectf{0, 0, 48.f, 48.f}} };
		Enemy::BehaviourSet turretBehaviour{};
		turretBehaviour.fightingBehaviour = new TurretBehaviour(m_pPlayer, *m_pLevel);
		turretBehaviour.drawingBehaviour = new TurretDrawing();

		Enemy* newEnemy{ new Enemy{ Actor::ActorData{pos, Actor::Dimension{48.f, 48.f, Rectf{0, 0, 48.f, 48.f}}}, turretBehaviour, 400.f, 1 } };
		newEnemy->EquipGun(new Gun(0.5f, 400.f, 0.1f, nullptr, BulletType::light));
		return newEnemy;
	}
		break;
	default:
		return nullptr;
		break;
	}
}

//Enemy* EnemyFactory::CreateRandomEnemy(const Point2f& pos)
//{
//
//}