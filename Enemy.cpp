#include "Classes/Enemy.h"
Enemy::Enemy()
{
	shipType = 1;
	movementDirection = sf::Vector2f(0, 0);
	fireRate = 10;
	damage = 25;
	speedVec = sf::Vector2f(-(200 + std::rand()%300), 0);
	enemyLvl = (1-abs(speedVec.x) / 1300)*10;
	hp = enemyLvl* 20;
	position = sf::Vector2f(WINX + 400, 50+std::rand()%(WINY-50));
	collisionBox.setRadius(30);
	collisionBox.setOrigin(collisionBox.getRadius(), collisionBox.getRadius());
	collisionBox.setFillColor(sf::Color(255, 0, 0, 100));
	renderRect = sf::IntRect(0, 112, 110, 39);
	shipSprite.setTextureRect(renderRect);
	shipSprite.scale(sf::Vector2f(-1, 1));
	shipSprite.setOrigin(70, 20);
};
void Enemy::updateEnemy(float dt) {

	if (this->position.y > (WINY)- this->collisionBox.getRadius()) {
		speedVec.y -= 100;
	}
	if (this->position.y < 0 + this->collisionBox.getRadius()) {
		speedVec.y += 100;
	}

	this->position.x = this->position.x + this->speedVec.x * dt;
	this->position.y = this->position.y + this->speedVec.y * dt;
	this->speedVec.y *= 0.98;
	this->collisionBox.setPosition(position);
	this->shipSprite.setPosition(position);
}
