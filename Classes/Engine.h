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
#include "Animation.h"
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
	void shootProjectile(Ship &ship);
	void spawnEnemy();
	AI ai;
	Animation animation;
	sf::Clock dtclock;
	sf::Clock animClock;
	sf::Font arial;

	bool debugFlag;
	int tick;
	int lastAnimationTick;
	int lastSpawnTick;
	float slowMotion;
	float dt;
private:
	sf::RenderWindow window;
	void processEvents();
	void update(float dt);
	void render();
};
