#include "Classes/AI.h"

void AI::movementUpdate(vector<Enemy>& enemyShip, Ship& player, vector<Projectile>& projectileList, float dt)
{
	for (unsigned int i = 0; i < projectileList.size(); i++) {
		projectileList[i].updateProjectile(dt);
	}
	for (unsigned int i = 0; i < enemyShip.size(); i++) {
		enemyShip[i].Enemy::updateEnemy(dt);
	}
	detectCollision(enemyShip, player, projectileList, dt);
}

void AI::detectCollision(vector<Enemy>& enemyShip, Ship& player, vector<Projectile>& projectileList, float dt)
{
	for (unsigned int i = 0; i < enemyShip.size(); i++) {
		float r1 = 0; float ax = enemyShip[i].position.x; float ay = enemyShip[i].position.y;
		r1 = enemyShip[i].collisionBox.getRadius();
		for (unsigned int j = 0; j < projectileList.size(); j++) {
			float r2 = 0; float dist = 0; float bx = projectileList[j].position.x; float by = projectileList[j].position.y;
			r2 = projectileList[j].collisionBox.getRadius();
			dist = std::sqrt(((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
			if (r1 + r2 >= dist) {
				enemyShip[i].hp = enemyShip[i].hp - projectileList[j].damage;
				projectileList[j].damage = 0;
				projectileList[j].state = 2; ///fixed it. Welp, it was using different index i instead of j...


			}
		}
	}
	trashRemoval(enemyShip, player, projectileList);
}

void AI::trashRemoval(vector<Enemy>& enemyShip, Ship& player, vector<Projectile>& projectileList)
{
	for (unsigned int i = 0; i < projectileList.size(); i++) {
		//Remove obsolete objects
		if (projectileList[i].position.x > 3000 ||
			projectileList[i].position.x < -1000 ||
			projectileList[i].position.y> 3000 ||
			projectileList[i].position.y < -1000 ||
			projectileList[i].state == 3 ) //state 3 is removal state, it's set after animation loop is done
		{
			projectileList.erase(projectileList.begin() + i);
		}
	}
	for (unsigned int i = 0; i < enemyShip.size(); i++) {

		if (enemyShip[i].position.x > 4000 || 
			enemyShip[i].position.x < -1000 || 
			enemyShip[i].position.y> 3000 || 
			enemyShip[i].position.y < -1000	|| 
			enemyShip[i].hp <= 0) 
			enemyShip.erase(enemyShip.begin() + i);
	}
	avoidSpawnCollision(enemyShip);
}

void AI::avoidSpawnCollision(vector<Enemy>& enemyShip)
{
	for (unsigned int i = 0; i < enemyShip.size(); i++) {
		float r1 = enemyShip[i].collisionBox.getRadius() + 20; float ax = enemyShip[i].position.x; float ay = enemyShip[i].position.y;
		for (unsigned int j = 0; j < enemyShip.size(); j++) {
			float r2 = enemyShip[j].collisionBox.getRadius() + 20; float dist = 0; float bx = enemyShip[j].position.x; float by = enemyShip[j].position.y;
			dist = std::sqrt(((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
			
			if (r1 + r2 >= dist && i != j) {
				if (enemyShip[i].position.y < enemyShip[j].position.y) {
					enemyShip[j].speedVec.y += 5;
					enemyShip[i].speedVec.y -= 5;
				}
				else 
				{
					enemyShip[i].speedVec.y += 5;
					enemyShip[j].speedVec.y -= 5;
				}
			}
		}
	}
}
