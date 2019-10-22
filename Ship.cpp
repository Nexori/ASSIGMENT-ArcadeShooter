#include "Ship.h"

Ship::Ship()
{
	fireRate = 300;
	hp = 100;
	damage = 25;
	speedVec = sf::Vector2f(0, 0);
	position = sf::Vector2f(WINX/4,WINY/2);
	shape = sf::CircleShape(25);
	shape.setFillColor(sf::Color::Red);
}
Ship::~Ship()
{
}
bool Ship::canShoot(int lastTick, int Tick) {
	if (Tick - lastTick > 3600/fireRate) return true;
	else return false;
}

void Ship::update(float dt)
{
	if (this->position.y > (WINY)) {
		speedVec.y = speedVec.y - 100;
	}
	if (this->position.y < 0) {
		speedVec.y = speedVec.y + 100;
	}
	if (this->position.x < 0) {
		speedVec.x += 100;
	}
	if (this->position.x > WINX) {
		speedVec.x -= 100;
	}
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
