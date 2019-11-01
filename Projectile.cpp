#include "Classes/Projectile.h"
Projectile::Projectile(sf::Vector2f playerPos, sf::Vector2f playerSpeed, float damage, sf::Vector2f offset, int projectileOwner) {
	this->offset = offset;
	this->projectileOwner = projectileOwner;
	this->state = 0;
	this->damage = damage;
	this->position = playerPos + offset;
	this->speedVec = playerSpeed;
	this->speedVec.x = speedVec.x + 2000;
	this->tempspeedVec = speedVec;

	collisionBox.setRadius(14); collisionBox.setFillColor(sf::Color(255,255,0,100)); collisionBox.setPosition(position);
	collisionBox.setOrigin(collisionBox.getRadius(), collisionBox.getRadius());

	std::cout.precision(5);
	std::cout << "\n[DEBUG]Projectile constructor position\t Position:";
	std::cout << playerPos.x<< " || " << playerPos.y << 
		"\tSpeed :" << playerSpeed.x << " || " << playerSpeed.y << "\tOffset:" << offset.x << " || " << offset.y;
	if (projectileOwner)
	{
		renderRect = IntRect(0, 60, 70, 50);
	}
	else renderRect = IntRect(0, 12, 40, 40);
	projectileSprite.setTextureRect(renderRect);
	projectileSprite.scale(sf::Vector2f(2, 1.5));
	projectileSprite.setOrigin(sf::Vector2f(20,20));
	
	frameState = 0;
}


void Projectile::updateProjectile(float dt)
{
	this->position.x = position.x + speedVec.x * dt;
	this->position.y = position.y + speedVec.y * dt;
	this->speedVec.y *= 0.9;
	this->collisionBox.setPosition(position);
	this->projectileSprite.setPosition(position);

}

void Projectile::projectileDraw(sf::RenderWindow& window)
{
	//window.draw(collisionBox);
	window.draw(projectileSprite);
}
