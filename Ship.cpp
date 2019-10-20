#include "Ship.h"

Ship::Ship()
{
	hp = 50;
	speedVec = sf::Vector2f(0, 0);
	position = sf::Vector2f(WINX/4,WINY/2);
	shape = sf::CircleShape(25);
	shape.setFillColor(sf::Color::Red);
}

Ship::~Ship()
{
}

void Ship::update(float dt)
{
	this->position.x = this->position.x + this->speedVec.x * dt;
	this->position.y = this->position.y + this->speedVec.y * dt;
	this->speedVec.x *= 0.85;
	this->speedVec.y *= 0.85;
	this->shape.setPosition(position);
}

void Ship::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
