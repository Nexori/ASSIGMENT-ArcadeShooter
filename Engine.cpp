#include "Engine.h"

Engine::Engine() : window(sf::VideoMode(WINX,WINY),"Arcade Space Game")
{
	srand(time(NULL));
	this->window.setFramerateLimit(60);
	this->dt = 0;
	this->slowMotion = 1;
	arial.loadFromFile("arial.ttf");
	this->tick = 0;
	this->lastAnimationTick = 0;
	this->lastSpawnTick = 0;
	player.collisionBox.setOrigin(40, 20);
	animation.textureAtlas.loadFromFile("textures.png");
	animation.initialize(player, enemyShip, projectileList);
}

void Engine::run()
{
	while (window.isOpen())
	{
		dt = clock.restart().asSeconds();
		processEvents();
		update(dt/slowMotion);
		render();
		tick++;
	}
}

void Engine::spawnEnemy() {
	if (enemyShip.size() < 50 && canSpawn(lastSpawnTick, tick) == true) {
		enemyShip.push_back(Enemy());
		enemyShip[enemyShip.size()-1].shipSprite.setTexture(animation.textureAtlas);
		cout << "\n[DEBUG]Enemy spawned";
		lastSpawnTick = tick;
	}
	else if (enemyShip.size() > 50) cout << "\n[DEBUG]Too many enemies";
	else cout << "\n[DEBUG]Spawning cooldown";
}

void Engine::shootProjectile(Ship& ship) {
	if (ship.canShoot(ship.lastShootTick, tick)) 
	{
		ship.spawnProjectile(ship, tick, sf::Vector2f(0, -3), sf::Vector2f(0, 13), false, projectileList);
		projectileList[projectileList.size()-1].projectileSprite.setTexture(animation.textureAtlas);
		projectileList[projectileList.size()-2].projectileSprite.setTexture(animation.textureAtlas);
	}
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
		slowMotion = 1;
		player = Ship();
		enemyShip.clear();
		projectileList.clear();
		animation.initialize(player, enemyShip, projectileList);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		shootProjectile(player);
	}
	//remove later
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		spawnEnemy();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
		slowMotion *= 0.99;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
		slowMotion *= 1.01;
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
	animation.update(dt, player , enemyShip, projectileList);

	//Trash removal
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

	//Collision detection (circles)
	for (int i = 0; i < enemyShip.size(); i++) {
		float r1 = 0; float ax = enemyShip[i].position.x; float ay = enemyShip[i].position.y;
		r1 = enemyShip[i].collisionBox.getRadius();
		for (int j = 0; j < projectileList.size(); j++) {
			float r2 = 0; float dist = 0; float bx = projectileList[j].position.x; float by = projectileList[j].position.y;
			 r2 = projectileList[j].collisionBox.getRadius();
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
	test << "FPS: " << 1 / dt << "\nSpeedvec:" << player.speedVec.x << "  |  " << player.speedVec.y << "\nSimspeed: " << 1/slowMotion << "\nCanSpawn: " << canSpawn(lastSpawnTick, tick) << "\nBullet cnt.: " << projectileList.size();
	sf::String temp(test.str());
	sf::Text temphelp(temp, arial, 20);

	window.clear();
	player.draw(window);

	for (int i = 0; i < enemyShip.size(); i++) {
		enemyShip[i].Ship::draw(window);
		//window.draw(enemyShip[i].shipSprite);
		std::ostringstream dbgnfo;
		dbgnfo << "HP: " << enemyShip[i].hp << "\nLV: " << enemyShip[i].enemyLvl;
		sf::String tmp(dbgnfo.str());
		sf::Text dbgnfotxt(tmp, arial, 20);
		dbgnfotxt.setPosition(enemyShip[i].position);
		window.draw(dbgnfotxt);
	}
	for (int i = 0; i < projectileList.size(); i++) {
		projectileList[i].projectileDraw(window);
	}
	window.draw(temphelp);
	window.display();
}

bool Engine::canSpawn(int lastTick, int Tick) {
	if (Tick - lastTick > 20) return true;
	else return false;
}