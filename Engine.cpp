#include "Engine.h"
/*
TODO:
[x]	RTTI dynamic_cast etc (propably not, depends if polimorphysm is implemented)
[x]	Exceptions (texture handling)
[x] Polymorphism (will be in GUI)
[x] Templates? (not sure if possible here)
[~] I/O streams (debug info uses sstream and it's commands)
[x] Multiple inheritance (not jet, possibly in GUI)
[v] Inheritance (Many present)

General requirements:
[v] 5<= indepentent classes requirement
[x] 4<= ideas implemented on labs
*/
Engine::Engine() : window(sf::VideoMode(WINX,WINY),"Arcade Space Game")
{
	this->debugFlag = false;
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
	player.frameState = animClock.getElapsedTime().asSeconds();
}

void Engine::run()
{
	while (window.isOpen())
	{
		dt = dtclock.restart().asSeconds();
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
		ship.spawnProjectile(ship, tick, sf::Vector2f(0,5), sf::Vector2f(0, 0), false, projectileList);
		projectileList[projectileList.size()-1].projectileSprite.setTexture(animation.textureAtlas);
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
		if (event.type == sf::Event::KeyPressed){
			if (event.key.code == sf::Keyboard::F12) {
				debugFlag = !debugFlag;
				if (debugFlag) {
					animation.textureAtlas.loadFromFile("texturesdebug.png");
				}
				else animation.textureAtlas.loadFromFile("textures.png");
			}
			if (event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
		}
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
	ai.movementUpdate(enemyShip, player, projectileList,dt);
	
	animation.update(animClock, player, enemyShip, projectileList);
}

void Engine::render()
{
	std::ostringstream test;
		if (debugFlag) {
			test << "DEBUG INFO:\nFPS: " << 1 / dt
				<< "\nSpeedvec:" << player.speedVec.x << "  <>  " << player.speedVec.y
				<< "\nSimspeed: " << 1 / slowMotion
				<< "\nCanSpawn: " << canSpawn(lastSpawnTick, tick)
				<< "\nBullet cnt.: " << projectileList.size()
				<< "\nEnemies cnt.: " << enemyShip.size()
				<< "\nPlayer animation rect:." << player.renderRect.left << "  <>  " << player.renderRect.top << "  <>  " << player.renderRect.width << "  <>  " << player.renderRect.height; ;
		}
		else { test << "Press F12 for debug info"; }

	sf::String temp(test.str());
	sf::Text temphelp(temp, arial, 20);

	window.clear();
	player.draw(window);

	for (unsigned int i = 0; i < enemyShip.size(); i++) {
		enemyShip[i].Ship::draw(window);
		//window.draw(enemyShip[i].shipSprite);
		std::ostringstream dbgnfo;
		if (debugFlag) 
		{
			dbgnfo << "HP: " << enemyShip[i].hp << "\nLV: " << enemyShip[i].enemyLvl;
			sf::String tmp(dbgnfo.str());
			sf::Text dbgnfotxt(tmp, arial, 20);
			dbgnfotxt.setPosition(enemyShip[i].position);
			dbgnfotxt.setColor(sf::Color::Yellow);
			window.draw(dbgnfotxt);
		}
	}
	for (unsigned int i = 0; i < projectileList.size(); i++) {
		projectileList[i].projectileDraw(window);
	}
	window.draw(temphelp);
	window.display();
}

bool Engine::canSpawn(int lastTick, int Tick) {
	if (Tick - lastTick > 20) return true;
	else return false;
}