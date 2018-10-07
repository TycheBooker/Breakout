#pragma once
#include <SFML/Graphics.hpp>
#include "StateManager.h"

class BaseScreen
{
public:
	BaseScreen();
	BaseScreen(StateManager * stateManager);
	virtual ~BaseScreen();

	virtual void renderScreen(sf::RenderWindow &window) = 0;
	virtual void updateScreen(sf::Time deltaTime) = 0;
	virtual void handleInput(sf::Event) = 0;

protected:
	StateManager * stateManager;
};

