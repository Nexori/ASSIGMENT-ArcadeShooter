#include "Projectile.h"
Projectile::Projectile() {
	damage = 0;
}

Projectile::Projectile(sf::Vector2f playerPos, sf::Vector2f playerSpeed, float damage) {
	position = playerPos;
	speedVec = playerSpeed;
	speedVec.x = speedVec.x + 2000;
	shape.setRadius(5); shape.setFillColor(sf::Color::Cyan); shape.setPosition(position);
	shape.setOrigin(shape.getRadius() / 2, shape.getRadius() / 2);
	this->damage = damage;
	std::cout << "\n[DEBUG]Projectile constructor position\n Position:";
	std::cout << playerPos.x<< " || " << playerPos.y << 
		"\nSpeed :" << playerSpeed.x << " || " << playerSpeed.y << std::endl;
}

Projectile::~Projectile() {

}

void Projectile::updateProjectile(float dt)
{
	position.x = position.x + speedVec.x * dt;
	position.y = position.y + speedVec.y * dt;
	speedVec.y *= 0.9;
	shape.setPosition(position);

}

void Projectile::projectileDraw(sf::RenderWindow& window)
{
	window.draw(shape);
}
