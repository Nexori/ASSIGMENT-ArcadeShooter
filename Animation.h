#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Enemy.h"
using namespace std;
using namespace sf;
struct Frame
{
	sf::IntRect state;
	double timeTick;
};
class Animation
{
public:
	Animation();
	~Animation() {};
	vector<Frame> frameVector;
	sf::Texture textureAtlas;
	void update(double time,Ship &player, vector<Enemy> &enemyShips, vector<Projectile> &bullets);
	void addFrame(Frame& frame);
		
};

