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
using namespace sf;
using namespace std;


class Engine
{
public:
	Engine();
	void run();
	sf::Clock clock;
	sf::Font arial;
	Ship player;
	double dt;
private:
	sf::RenderWindow window;
	void processEvents();
	void update(float dt);
	void render();
};
