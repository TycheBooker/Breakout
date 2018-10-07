#include "Game.h"

Game::Game() :
	window(sf::VideoMode(windowWidth, windowHeight), "Memory"),
	stateManager(&window),
	musicPlayer()
{
	window.setFramerateLimit(windowFramerate);
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	musicPlayer.playMusic();
	stateManager.switchScreen(Screen::StartScreen);
	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		processInput();
		update(deltaTime);
		render();
	}
}

void Game::processInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if ((event.type == sf::Event::Closed) ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
			window.close();
		}
		stateManager.getCurrentScreen()->handleInput(event);
	}
}

void Game::update(sf::Time deltaTime)
{
	stateManager.getCurrentScreen()->updateScreen(deltaTime);
}

void Game::render()
{
	window.clear(sf::Color::Black);
	renderScreen();
	window.display();
}

void Game::renderScreen()
{
	stateManager.getCurrentScreen()->renderScreen(window);
}
