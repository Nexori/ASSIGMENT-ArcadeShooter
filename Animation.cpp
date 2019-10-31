#include "Animation.h"
Animation::Animation() {
	//textureAtlas.loadFromFile("textures.png");
	//Initiate animation frames
	//for (int i = 0; i < 6; i++) {
	//	temp.state = IntRect(0+i*40, 12, 40, 40);
	//	temp.duration = 4;
	//	frameVector.push_back(temp);
	//}
	////player impact
	//for (int i = 0; i < 5; i++) {
	//	temp.state = IntRect(200 + i * 40, 12, 40, 40);
	//	temp.duration = 4;
	//	frameVector.push_back(temp);
	//}
	////player movement
	//for (int i = 0; i < 6; i++) {
	//	temp.state = IntRect(0 + i * 104, 151, 104, 34);
	//	temp.duration = 4;
	//	frameVector.push_back(temp);
	//}
	////player movement
	//for (int i = 0; i < 4; i++) {
	//	temp.state = IntRect(0 + i * 104, 151, 104, 34);
	//	temp.duration = 4;
	//	frameVector.push_back(temp);
	//}
	////enemy shoot
	//for (int i = 0; i < 4; i++) {
	//	temp.state = IntRect(0 + i * 70,60, 70, 50);
	//	temp.duration = 4;
	//	frameVector.push_back(temp);
	//}
	////enemy impact
	//for (int i = 0; i < 5; i++) {
	//	temp.state = IntRect(280 + i * 70, 60, 70, 50);
	//	temp.duration = 4;
	//	frameVector.push_back(temp);
	//}
	////enemy movement
	//for (int i = 0; i < 4; i++) {
	//	temp.state = IntRect(0 + i * 110, 112, 110, 39);
	//	temp.duration = 4;
	//	frameVector.push_back(temp);
	//}
	/*Thus 
	Player animations:
	0-4 player shooting, 5 player bolt, 6-10 player bolt impact, 11-14 player moving, 15-16 player idle

	Enemy animations:
	17-21 enemy shooting, 22 enemy bolt, 23-28 enemy bolt impact, 29-32 enemy moving;
	
	*/
};
void Animation::initialize(Ship& player, vector<Enemy>& enemyShips, vector<Projectile>& bullets) {
	player.shipSprite.setTexture(textureAtlas);
}
void Animation::update(Clock time, Ship& player, vector<Enemy>& enemyShips, vector<Projectile>& bullets)
{	

	elapsedTime = time.getElapsedTime().asSeconds();
	updatePlayer(player);
	for (int i = 0; i < enemyShips.size(); i++){
		updateEnemy(enemyShips[i]);
	}
	for (int i = 0; i < bullets.size(); i++) {
		updateProjectile(bullets[i]);
		if (bullets[i].renderRect.left >  7 * 70 && bullets[i].projectileOwner == 1) 
			bullets.erase(bullets.cbegin()+i);
	}
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].renderRect.left > 10 * 40 && bullets[i].projectileOwner == 0)
			bullets.erase(bullets.cbegin() + i);
	}
}
void Animation::updatePlayer(Ship& player) {
	player.frameState += player.animClock.restart().asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (0.15 <= player.frameState) {
			player.renderRect.left += 104;
			player.frameState = 0;
		}
		if (player.renderRect.left >= 416) player.renderRect.left = 0;
	}
	else
		if (0.3 <= player.frameState)
	{
		if (player.renderRect.left < 416) player.renderRect.left = 416;
		player.renderRect.left += 104;
		player.frameState = 0;
		if (player.renderRect.left >= 6*104) player.renderRect.left = 416;
	}
	
	player.shipSprite.setTextureRect(player.renderRect);
}

void Animation::updateEnemy(Enemy& enemy) {
	enemy.frameState += enemy.animClock.restart().asSeconds();
	if (0.25 <= enemy.frameState) 
	{
		enemy.renderRect.left += 110;
		enemy.frameState = 0;
	}
	if (enemy.renderRect.left >= 4*110) enemy.renderRect.left = 0;
	enemy.shipSprite.setTextureRect(enemy.renderRect);
}
void Animation::updateProjectile(Projectile& projectile) 
{
	projectile.frameState += projectile.animClock.restart().asSeconds();
	if (projectile.projectileOwner)
	{
	//Enemy 70x50

		//Launch
		if (projectile.state == 0 && 0.05 <= projectile.frameState)
		{
		projectile.renderRect.left += 70;
		projectile.frameState = 0;
		if (projectile.renderRect.left > 2 * 70)
			projectile.state = 1;
		}
		//Flight
		if (projectile.state == 1)
		{
			projectile.renderRect.left = 3 * 70;
		}
		//Impact
		if (projectile.state == 2 && 0.05 <= projectile.frameState)
		{
			if (projectile.renderRect.left < 4 * 70) {
				projectile.renderRect.left = 280;
			}
			projectile.renderRect.left += 70;
			projectile.frameState = 0;

		}
	}
	//Player 40x40
	else {

		//Launch
		if (projectile.state == 0 && 0.05 <= projectile.frameState)
		{
			projectile.renderRect.left += 40;
			projectile.frameState = 0;
			if (projectile.renderRect.left > 4 * 40)
				projectile.state = 1;
		}
		//Flight
		if (projectile.state == 1)
		{
			projectile.renderRect.left = 5 * 40;
		}
		//Impact
		if (projectile.state == 2 && 0.05 <= projectile.frameState)
		{
			if (projectile.renderRect.left < 6 * 40) {
				projectile.renderRect.left = 6*40;
			}
			projectile.renderRect.left += 40;
			projectile.frameState = 0;

		}
	}
	projectile.projectileSprite.setTextureRect(projectile.renderRect);
}