#pragma once
#include <unordered_set>
#include "Enemy.h"
class Player;
class Level;



class EnemyFactory
{
public:
	EnemyFactory(Player* player, Level* level, const std::initializer_list<Enemy::Type> allowedTypes);
	//~EnemyFactory();

	void AllowRandomCreationOfType(Enemy::Type type);
	void DisallowRandomCreationOfType(Enemy::Type type);

	Enemy* CreateEnemyOfType(Enemy::Type type, const Point2f& leftBottom);
	//Enemy* CreateRandomEnemy();

private:
	std::unordered_set<Enemy::Type> m_RandomSpawnableEnemyTypes;
	Player* m_pPlayer;
	Level* m_pLevel;
};

