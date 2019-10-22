#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Main.hpp>

class Projectile
{
public:
	Projectile();
	Projectile(sf::Vector2f playerPos, sf::Vector2f playerSpeed, float damage);
	~Projectile();
	//Position
	sf::Vector2f position;
	sf::Vector2f speedVec;
	//Render
	sf::Texture projectileTexture;
	sf::Texture projectileSprite;
	sf::CircleShape shape;
	//Variable
	float damage;
	//Methods
	void updateProjectile(float dt);
	void projectileDraw(sf::RenderWindow& window);
};

