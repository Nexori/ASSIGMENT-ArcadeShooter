#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "Constants.h"
class Ship
{
public:
	Ship();
	~Ship();
		//Position
	sf::Vector2f position;
	sf::Vector2f speedVec;
		//Render
	sf::Texture playerTexture;
	sf::Texture playerSprite;
	sf::CircleShape shape;
		//Variables
	float fireRate;
	float hp;
	float damage;
		//Methods
	bool canShoot(int lastTick, int Tick);
	void update(float dt);
	void draw(sf::RenderWindow& window);
};
