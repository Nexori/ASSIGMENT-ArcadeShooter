#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Main.hpp>
using namespace std;
using namespace sf;
class Projectile
{
public:
	Projectile();
	Projectile(sf::Vector2f playerPos, sf::Vector2f playerSpeed, float damage, Vector2f offset);
	~Projectile() {};
	//Position
	sf::Vector2f offset;
	sf::Vector2f position;
	sf::Vector2f speedVec;
	//Render
	sf::CircleShape shape;
	//Variable
	float damage;
	//Methods
	void updateProjectile(float dt);
	void projectileDraw(sf::RenderWindow& window);
};

