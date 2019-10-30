#include "Projectile.h"
Projectile::Projectile() {
	damage = 0; projectileOwner = 0;
}

Projectile::Projectile(sf::Vector2f playerPos, sf::Vector2f playerSpeed, float damage, sf::Vector2f offset, int projectileOwner, int order) {
	this->offset = offset;
	this->projectileOwner = projectileOwner;
	position = playerPos + offset;
	speedVec = playerSpeed;
	speedVec.x = speedVec.x + 2000;
	collisionBox.setRadius(5); collisionBox.setFillColor(sf::Color(255,255,0,100)); collisionBox.setPosition(position);
	collisionBox.setOrigin(collisionBox.getRadius(), collisionBox.getRadius());
	this->damage = damage;
	std::cout.precision(5);
	std::cout << "\n[DEBUG]Projectile constructor position\t Position:";
	std::cout << playerPos.x<< " || " << playerPos.y << 
		"\tSpeed :" << playerSpeed.x << " || " << playerSpeed.y << "\tOffset:" << offset.x << " || " << offset.y;
	if (projectileOwner == 0 && order == 0) renderRect = sf::IntRect(414, 26, 10, 2);
	if (projectileOwner == 0 && order == 1) renderRect = sf::IntRect(414, 37, 10, 2);
	if (projectileOwner == 1 && order == 1) renderRect = sf::IntRect(225, 92, 18, 4);
	if (projectileOwner == 1 && order == 0) renderRect = sf::IntRect(225, 81, 18, 4);
	projectileSprite.setTextureRect(renderRect);
	projectileSprite.scale(sf::Vector2f(1.5, 1.25));
}


void Projectile::updateProjectile(float dt)
{
	position.x = position.x + speedVec.x * dt;
	position.y = position.y + speedVec.y * dt;
	speedVec.y *= 0.9;
	collisionBox.setPosition(position);
	projectileSprite.setPosition(position);

}

void Projectile::projectileDraw(sf::RenderWindow& window)
{
	//window.draw(collisionBox);
	window.draw(projectileSprite);
}
