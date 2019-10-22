#include "Engine.h"

Engine::Engine() : window(sf::VideoMode(WINX,WINY),"Arcade Space Game")
{
	srand(time(NULL));
	this->window.setFramerateLimit(60);
	this->dt = 0;
	arial.loadFromFile("arial.ttf");
	this->tick = 0;
	this->lastShootTick = 0;
	this->lastSpawnTick = 0;
	player.shape.setOrigin(player.shape.getRadius(), player.shape.getRadius());
}

void Engine::run()
{
	while (window.isOpen())
	{
		dt = clock.restart().asSeconds();
		processEvents();
		update(dt);
		render();
		tick++;
	}
}
void Engine::spawnEnemy() {
	if (enemyShip.size() < 50 && canSpawn(lastSpawnTick, tick) == true) {
		enemyShip.push_back(Enemy());
		cout << "\n[DEBUG]Enemy spawned";
		lastSpawnTick = tick;
	}
	else if (enemyShip.size() > 50) cout << "\n[DEBUG]Too many enemies";
	else cout << "\n[DEBUG]Spawning cooldown";
}
void Engine::spawnProjectile(Ship& ship)
{
	if (ship.canShoot(lastShootTick, tick) == true) {
		projectileList.push_back(Projectile(ship.position, ship.speedVec, ship.damage));
		cout << "\n[DEBUG]Projectile vec size: " << projectileList.size() << endl;
		lastShootTick = tick;
	}
	else cout << "\n[DEBUG] Can't shoot, cooldown";
}

void Engine::processEvents()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.position.y > -15) {
		player.speedVec.y -= 120;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.position.y < WINY - 15 ) {
		player.speedVec.y += 120;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.position.x > -15) {
		player.speedVec.x -= 120;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.position.x < WINX - 10) {
		player.speedVec.x += 120;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		player = Ship();
		enemyShip.clear();
		projectileList.clear();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		spawnProjectile(player);
	}
	//remove later
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		spawnEnemy();
	}
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			std::cout << "[INFO] Window closed";
			window.close();
		}
	}
}

void Engine::update(float dt)
{
	player.update(dt);
	for (int i = 0; i < projectileList.size(); i++) {
		projectileList[i].updateProjectile(dt);
		//Remove obsolete objects
		if (projectileList[i].position.x > 3000 || projectileList[i].position.x 
			< -1000 || projectileList[i].position.y> 3000 || projectileList[i].position.y < -1000) 
		{
			projectileList.erase(projectileList.begin()+i);
		}
	}
	for (int i = 0; i < enemyShip.size(); i++){
		enemyShip[i].Enemy::updateEnemy(dt);
		if (enemyShip[i].position.x > 3000 || enemyShip[i].position.x
			< -1000 || enemyShip[i].position.y> 3000 || enemyShip[i].position.y < -1000)
		{
			enemyShip.erase(enemyShip.begin() + i);
		}
	}
	for (int i = 0; i < enemyShip.size(); i++) {
		float r1 = 0; float ax = enemyShip[i].position.x; float ay = enemyShip[i].position.y;
		r1 = enemyShip[i].shape.getRadius();
		for (int j = 0; j < projectileList.size(); j++) {
			float r2 = 0; float dist = 0; float bx = projectileList[j].position.x; float by = projectileList[j].position.y;
			 r2 = projectileList[j].shape.getRadius();
			 dist = std::sqrt(((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
			 if (r1 + r2 >= dist) {
				 enemyShip[i].hp = enemyShip[i].hp - projectileList[j].damage;
				 projectileList.erase(projectileList.begin() + j);
				 if (enemyShip[i].hp <= 0) {
					 enemyShip.erase(enemyShip.begin() + i);
				 }
			 }
		}
	}
}

void Engine::render()
{
	std::ostringstream test;
	test << "FPS:\n" << 1 / dt << "\nSpeedvec:\n" << player.speedVec.x << "  |  " << player.speedVec.y << "\nPlayerPos:\n" << player.position.x << "  |  " << player.position.y << "\n dTick " << tick - lastShootTick << "\nCanShoot: " << player.canShoot(lastShootTick, tick) << "\nCanSpawn: " << canSpawn(lastSpawnTick, tick);
	sf::String temp(test.str());
	sf::Text temphelp(temp, arial, 20);

	window.clear();
	player.draw(window);
	for (int i = 0; i < projectileList.size(); i++) {
		projectileList[i].projectileDraw(window);
	}
	for (int i = 0; i < enemyShip.size(); i++) {
		enemyShip[i].draw(window);
	}
	window.draw(temphelp);
	window.display();
}
bool Engine::canSpawn(int lastTick, int Tick) {
	if (Tick - lastTick > 20) return true;
	else return false;
}