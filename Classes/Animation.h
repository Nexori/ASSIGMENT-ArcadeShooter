#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "AI.h"
using namespace std;
using namespace sf;

class Animation
{
private:
	sf::Vector2f playerPos;
	sf::Vector2f enemyPos;
	sf::Vector2f bulletPos;
public:
	Animation() { 
		elapsedTime = 0;
		playerPos = sf::Vector2f(0, 0);
		enemyPos = sf::Vector2f(0, 0);
		bulletPos = sf::Vector2f(0, 0);
	};
	~Animation() {};
	sf::Texture textureAtlas;
	double elapsedTime;
	void initialize(Ship& player, vector<Enemy>& enemyShips, vector<Projectile>& bullets);
	void update(Clock time,Ship &player, vector<Enemy> &enemyShips, vector<Projectile> &bullets);
	void updatePlayer(Ship& player);
	void updateEnemy(Enemy& player);
	void updateProjectile(Projectile& projectile, vector<Enemy>& enemyShips);
		
};

