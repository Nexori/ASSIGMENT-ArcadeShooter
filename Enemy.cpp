#include "Enemy.h"
Enemy::Enemy()
{
	movementDirection = sf::Vector2f(0, 0);
	fireRate = 10;
	damage = 25;
	speedVec = sf::Vector2f(-(200 + std::rand()%300), 0);
	enemyLvl = (1-abs(speedVec.x) / 1300)*10;
	hp = enemyLvl* 20;
	position = sf::Vector2f(WINX + 200, std::rand()%WINY);
	shape.setRadius(36);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setFillColor(sf::Color(255,0,0,100));
};
void Enemy::updateEnemy(float dt) {

	if (this->position.y > (WINY)) {
		speedVec.y += 100;
	}
	if (this->position.y < 0) {
		speedVec.y -= 100;
	}

	this->position.x = this->position.x + this->speedVec.x * dt;
	this->position.y = this->position.y + this->speedVec.y * dt;
	this->speedVec.x *= 0.999;
	this->speedVec.y *= 0.9;
	this->shape.setPosition(position);
}