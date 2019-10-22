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


#include "Ship.h"
#include "Projectile.h"
using namespace sf;
using namespace std;


class Engine
{
public:
	vector<Projectile> projectileList;
	vector<Ship> enemyShip;
	Ship player;

	Engine();
	void run();
	void spawnProjectile(Ship &ship);

	sf::Clock clock;
	sf::Font arial;

	int tick;
	int lastShootTick;
	double dt;
private:
	sf::RenderWindow window;
	void processEvents();
	void update(float dt);
	void render();
};
