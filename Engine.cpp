#include "Engine.h"

Engine::Engine() : window(sf::VideoMode(WINX,WINY),"Arcade Space Game")
{
	srand(time(NULL));
	this->window.setFramerateLimit(60);
	this->dt = 0;
	arial.loadFromFile("arial.ttf");
	dt = 0;
}

void Engine::run()
{
	while (window.isOpen())
	{
		dt = clock.restart().asSeconds();
		processEvents();
		update(dt);
		render();
	}
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
}

void Engine::render()
{
	std::ostringstream test;
	test << "FPS:\n" << 1 / dt << "\nSpeedvec:\n" << player.speedVec.x << "  |  " << player.speedVec.y << "\nPlayerPos:\n" << player.position.x << "  |  " << player.position.y;
	sf::String temp(test.str());
	sf::Text temphelp(temp, arial, 20);

	window.clear();
	player.draw(window);
	window.draw(temphelp);
	window.display();
}
