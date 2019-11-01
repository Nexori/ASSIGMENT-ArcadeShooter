#include "Animation.h"
void Animation::initialize(Ship& player, vector<Enemy>& enemyShips, vector<Projectile>& bullets) {
	player.shipSprite.setTexture(textureAtlas);
}
void Animation::update(Clock time, Ship& player, vector<Enemy>& enemyShips, vector<Projectile>& bullets)
{	

	elapsedTime = time.getElapsedTime().asSeconds();
	playerPos = player.position;
	updatePlayer(player);
	for (unsigned int i = 0; i < enemyShips.size(); i++){
		enemyPos = enemyShips[i].position;
		updateEnemy(enemyShips[i]);
	}
	for (unsigned int i = 0; i < bullets.size(); i++) {
		bulletPos = bullets[i].position;
		updateProjectile(bullets[i], enemyShips);
		if ((bullets[i].renderRect.left > 7 * 70 && bullets[i].projectileOwner == 1) ||
			(bullets[i].renderRect.left > 10 * 40 && bullets[i].projectileOwner == 0))
			bullets[i].state = 3;

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
void Animation::updateProjectile(Projectile& projectile, vector<Enemy>& enemies)
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
		if (projectile.state == 0)
		{

			if (0.05 <= projectile.frameState) 
			{
				projectile.renderRect.left += 40;
					projectile.frameState = 0;
					if (projectile.renderRect.left > 4 * 40)
						projectile.state = 1;
			}
			projectile.position.x = playerPos.x + projectile.offset.x;
			projectile.position.y = playerPos.y + projectile.offset.y;
		}
		//Flight
		if (projectile.state == 1)
		{
			projectile.renderRect.left = 5 * 40;
		}
		//Impact
		if (projectile.state == 2)
		{
		if (0.05 <= projectile.frameState)
		{
			if (projectile.renderRect.left < 6 * 40) 
			{
				projectile.renderRect.left = 6 * 40;
			}
			projectile.renderRect.left += 40;
			projectile.frameState = 0;
		}
			projectile.speedVec = sf::Vector2f(0, 0);
		}
	}
	projectile.projectileSprite.setTextureRect(projectile.renderRect);
}