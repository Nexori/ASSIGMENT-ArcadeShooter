#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>


#include "Enemy.h"
#include "Projectile.h"
using namespace sf;
using namespace std;


class Engine
{
public:
	vector<Projectile> projectileList;
	vector<Enemy> enemyShip;
	Ship player;

	Engine();
	void run();
	bool canSpawn(int lastTick, int Tick);
	void spawnProjectile(Ship &ship);
	void spawnEnemy();
	sf::Clock clock;
	sf::Font arial;

	int tick;
	int lastShootTick;
	int lastSpawnTick;
	double dt;
private:
	sf::RenderWindow window;
	void processEvents();
	void update(float dt);
	void render();
};
