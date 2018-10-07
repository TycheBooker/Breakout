#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include "BaseScreen.h"
#include "EndScreen.h"

class GameScreen : public BaseScreen
{
public:
	GameScreen(StateManager * stateManager);
	~GameScreen();

	virtual void renderScreen(sf::RenderWindow & window);
	virtual void updateScreen(sf::Time deltaTime);
	virtual void handleInput(sf::Event event);
private:
	void finishGame();

	//HUD * gameHUD;
};