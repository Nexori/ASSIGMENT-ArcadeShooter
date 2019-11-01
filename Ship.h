#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "Constants.h"
#include "Projectile.h"
class Ship
{
public:
	Ship();
	~Ship();
		//Position
	sf::Vector2f movementDirection;
	sf::Vector2f position;
	sf::Vector2f speedVec;
		//Render
	double frameState;
	sf::Clock animClock;
	sf::IntRect renderRect;
	sf::Sprite shipSprite;
	sf::CircleShape collisionBox;
		//Variables
	sf::Clock existanceTime;
	int shipType; // 0 - player, 1 - enemy
	int lastShootTick;
	float fireRate;
	float hp;
	float damage;
		//Methods
	bool canShoot(int lastTick, int Tick);
	void spawnProjectile(Ship ship, int tick, sf::Vector2f offsetA, sf::Vector2f offsetB, bool forced, std::vector<Projectile> &ProjectileList);
	void update(float dt);
	void draw(sf::RenderWindow& window);
};

