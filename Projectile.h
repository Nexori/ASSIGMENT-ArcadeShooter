#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Main.hpp>
using namespace std;
using namespace sf;

class Projectile
{
public:
	Projectile(sf::Vector2f playerPos, sf::Vector2f playerSpeed, float damage, Vector2f offset, int projectileOwner);
	~Projectile() {};
	//Position
	sf::Vector2f offset;
	sf::Vector2f position;
	sf::Vector2f speedVec;
	sf::Vector2f tempspeedVec;
	//Render
	double frameState;
	sf::Clock animClock;
	sf::IntRect renderRect;
	sf::Sprite projectileSprite;
	sf::CircleShape collisionBox;
	//Variable
	int state;//0-fired,1-flying,2-impact
	int projectileOwner; //0 - player, 1 - enemy
	float damage;
	//Methods
	void updateProjectile(float dt);
	void projectileDraw(sf::RenderWindow& window);
};

