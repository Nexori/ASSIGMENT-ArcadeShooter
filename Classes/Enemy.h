#pragma once
#include <random>
#include <vector>
#include "Ship.h"

class Enemy : public Ship
{
public:
	int enemyLvl;
	Enemy();
	~Enemy() {};
	void updateEnemy(float dt);
};

