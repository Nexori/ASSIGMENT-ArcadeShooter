#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Enemy.h"
using namespace std;
using namespace sf;

class Animation
{
public:
	//int frameIndex;
	Animation();
	~Animation() {};
	sf::Texture textureAtlas;
	double elapsedTime;
	void initialize(Ship& player, vector<Enemy>& enemyShips, vector<Projectile>& bullets);
	void update(Clock time,Ship &player, vector<Enemy> &enemyShips, vector<Projectile> &bullets);
	void updatePlayer(Ship& player);
	void updateEnemy(Enemy& player);
	void updateProjectile(Projectile& projectile);
		
};

