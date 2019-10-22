#include "Engine.h"

Engine::Engine() : window(sf::VideoMode(WINX,WINY),"Arcade Space Game")
{
	srand(time(NULL));
	this->window.setFramerateLimit(60);
	this->dt = 0;
	arial.loadFromFile("arial.ttf");
	this->tick = 0;
	this->lastShootTick = 0;
	player.shape.setOrigin(player.shape.getRadius() / 2, player.shape.getRadius() / 2);
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

void Engine::spawnProjectile(Ship& ship)
{
	if (ship.canShoot(lastShootTick, tick) == true) {
		projectileList.push_back(Projectile(ship.position, ship.speedVec, ship.damage));
		cout << "\n[DEBUG]Projectile vec size: " << projectileList.size() << endl;
		lastShootTick = tick;
	}
	else cout << "\n[DEBUG] Can't shoot, cooldown\n";
}

void Engine::processEvents()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player.speedVec.y -= 120;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player.speedVec.y += 120;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player.speedVec.x -= 120;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player.speedVec.x += 120;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		player = Ship();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		spawnProjectile(player);
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
		if (projectileList[i].position.x > 3000 || projectileList[i].position.x 
			< -1000 || projectileList[i].position.y> 3000 || projectileList[i].position.y < -1000) 
		{
			projectileList.erase(projectileList.begin()+i);
		}
	}
}

void Engine::render()
{
	std::ostringstream test;
	test << "FPS:\n" << 1 / dt << "\nSpeedvec:\n" << player.speedVec.x << "  |  " << player.speedVec.y << "\nPlayerPos:\n" << player.position.x << "  |  " << player.position.y << "\n dTick " << tick - lastShootTick << "\nCanShoot" << player.canShoot(lastShootTick, tick);;
	sf::String temp(test.str());
	sf::Text temphelp(temp, arial, 20);

	window.clear();
	player.draw(window);
	for (int i = 0; i < projectileList.size(); i++) {
		projectileList[i].projectileDraw(window);
	}
	window.draw(temphelp);
	window.display();
}
