#include "Ship.h"

Ship::Ship()
{
	shipType = 0;
	lastShootTick = 0;
	fireRate = 300;
	hp = 100;
	damage = 25;
	speedVec = sf::Vector2f(0, 0);
	position = sf::Vector2f(WINX/4,WINY/2);
	collisionBox.setRadius(25);
	collisionBox.setOrigin(collisionBox.getRadius()/2, collisionBox.getRadius()/2);
	collisionBox.setFillColor(sf::Color(0,255,0,100));
	renderRect = sf::IntRect(416,151,79,34);
	shipSprite.setTextureRect(renderRect);
	shipSprite.setOrigin(32, 15);
	shipSprite.setScale(sf::Vector2f(1.5, 1.5));
}
Ship::~Ship()
{
}
bool Ship::canShoot(int lastTick, int Tick) {
	if (Tick - lastTick > 3600/fireRate) return true;
	else return false;
}

void Ship::spawnProjectile(Ship ship, int tick, sf::Vector2f offsetA, sf::Vector2f offsetB , bool forced, std::vector<Projectile> &projectileList)
{
	if (ship.canShoot(lastShootTick, tick) == true || forced == true)
	{
		if (offsetB.x == 0 && offsetB.y == 0) {
			lastShootTick = tick;
			projectileList.push_back(Projectile(ship.position, ship.speedVec, ship.damage, offsetA,shipType,0));
		}
		if (offsetB.x != 0 || offsetB.y != 0) {
			lastShootTick = tick;
			projectileList.push_back(Projectile(ship.position, ship.speedVec, ship.damage, offsetA,shipType,0));
			projectileList.push_back(Projectile(ship.position, ship.speedVec, ship.damage, offsetB,shipType,1));
		}

	}
	else std::cout << "\n[DEBUG] Can't shoot, cooldown";
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
	this->collisionBox.setPosition(position);
	shipSprite.setPosition(position.x-30,position.y+2);
}
void Ship::draw(sf::RenderWindow& window)
{

	window.draw(shipSprite);
	window.draw(collisionBox);
}
