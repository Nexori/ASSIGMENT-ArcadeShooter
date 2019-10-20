#include "Player.h"
Player::Player() {
	hp = 100;
	speedVec = sf::Vector2f(0, 0);
	position = sf::Vector2f(20,WINY / 2);
	shape = sf::CircleShape(30);
	shape.setFillColor(sf::Color::Green);
}