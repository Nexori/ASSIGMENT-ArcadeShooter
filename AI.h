#pragma once
#include "Enemy.h"
class AI
{
public:
	void movementUpdate(vector<Enemy>& enemy, Ship& player, vector<Projectile>& projectile, float dt);
	void trashRemoval(vector<Enemy>& enemy, Ship& player, vector<Projectile>& projectile);
	void avoidSpawnCollision(vector<Enemy> &enemyList);
	void detectCollision(vector<Enemy> &enemy, Ship &player, vector<Projectile> &projectile,float dt);
};

