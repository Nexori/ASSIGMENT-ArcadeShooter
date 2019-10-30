#include "Animation.h"
Animation::Animation() {
	textureAtlas.loadFromFile("textures.png");
	//Player burn
	for (int i = 0; i < 4; i++) {
		Frame temp;
		temp.state = sf::IntRect(0+(i*105), 151, 105, 34);
		temp.timeTick=15;
		frameVector.push_back(temp);
	}
	//Player idle
	for (int i = 0; i < 2; i++) {
		Frame temp;
		temp.state = sf::IntRect(416 + (i * 79), 151, 79, 34);
		temp.timeTick = 15;
		frameVector.push_back(temp);
	}
	//Enemy burn
	for (int i = 0; i < 4; i++) {
		Frame temp;
		temp.state = sf::IntRect(0 + (i * 109), 112, 109, 39);
		temp.timeTick = 15;
		frameVector.push_back(temp);
	}
	//Enemy shoot
	Frame temp;
	temp.timeTick = 2;
	temp.state = sf::IntRect(3, 80, 3, 15);		frameVector.push_back(temp);//initial

	temp.state = sf::IntRect(65,73,23,11);		frameVector.push_back(temp);//top stage 1
	temp.state = sf::IntRect(128,68,48,17);		frameVector.push_back(temp);//top stage 2
	temp.state = sf::IntRect(225, 81, 18, 4);		frameVector.push_back(temp);//top basic
	temp.state = sf::IntRect(286, 73, 19, 13);		frameVector.push_back(temp);//impact top
	temp.state = sf::IntRect(348, 69, 25, 18);		frameVector.push_back(temp);//impact 2 top

	temp.state = sf::IntRect(409, 64, 39, 47);		frameVector.push_back(temp);//impact universal
	temp.state = sf::IntRect(475, 66, 36, 44);		frameVector.push_back(temp);//impact 1 universal

	temp.state = sf::IntRect(66, 90, 20, 11);		frameVector.push_back(temp);//bot stage 1
	temp.state = sf::IntRect(130, 88, 46, 19);		frameVector.push_back(temp);//bot stage 2
	temp.state = sf::IntRect(225, 92, 18, 4);		frameVector.push_back(temp);//bot basic
	temp.state = sf::IntRect(287, 91, 24, 14);		frameVector.push_back(temp);//impact bot
	temp.state = sf::IntRect(349, 89, 31, 19);		frameVector.push_back(temp);//impact 2 bot
	//Player shoot
	temp.state = sf::IntRect(16, 26, 3, 3);		frameVector.push_back(temp);//universal stage 1
	temp.state = sf::IntRect(79, 25, 5, 5);		frameVector.push_back(temp);//universal stage 2
	temp.state = sf::IntRect(142, 23, 11, 8);	frameVector.push_back(temp);//universal stage 3
	temp.state = sf::IntRect(205, 22, 17, 9);	frameVector.push_back(temp);//universal stage 4
	temp.state = sf::IntRect(269, 22, 25, 10);	frameVector.push_back(temp);//universal stage 5
	temp.state = sf::IntRect(333, 22, 10, 10);	frameVector.push_back(temp);//universal stage 6
	temp.state = sf::IntRect(414, 26, 10, 2);	frameVector.push_back(temp);//universal basic
	temp.state = sf::IntRect(482, 24, 8, 5);	frameVector.push_back(temp);//universal impact 1
	temp.state = sf::IntRect(548, 33, 12, 10);	frameVector.push_back(temp);//universal impact 2
	temp.state = sf::IntRect(269, 22, 25, 10);	frameVector.push_back(temp);//universal stage 5

};
void Animation::initialize(Ship& player, vector<Enemy>& enemyShips, vector<Projectile>& bullets) {
	player.shipSprite.setTexture(textureAtlas);
	for (int i = 0; i < bullets.size(); i++) bullets[i].projectileSprite.setTexture(textureAtlas);
}
void Animation::update(double time, Ship& player, vector<Enemy>& enemyShips, vector<Projectile>& bullets)
{
}

void Animation::addFrame(Frame& frame)
{
}