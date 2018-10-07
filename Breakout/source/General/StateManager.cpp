#include "StateManager.h"
#include "BaseScreen.h"
#include "StartScreen.h"
#include "GameScreen.h"
#include "EndScreen.h"

StateManager::StateManager(sf::RenderWindow * window) :
	score(0),
	dead(false),
	window(window)
{
}

StateManager::~StateManager()
{
	delete currentScreen;
	delete nextScreen;
}

void StateManager::switchScreen(Screen newScreen)
{
	if (nextScreen != nullptr)
	{
		delete nextScreen;
		nextScreen = nullptr;
	}

	switch (newScreen)
	{
	case Screen::StartScreen:
		nextScreen = new StartScreen(this);
		break;
	case Screen::GameScreen:
		nextScreen = new GameScreen(this);
		break;
	case Screen::EndScreen:
		nextScreen = new EndScreen(this);
		break;
	default:
		break;
	}

	if (nextScreen != nullptr)
	{
		std::swap(currentScreen, nextScreen);
	}
}

int StateManager::getScore()
{
	return score;
}

bool StateManager::isDead()
{
	return dead;
}

BaseScreen * StateManager::getCurrentScreen()
{
	return currentScreen;
}

sf::RenderWindow * StateManager::getWindow()
{
	return window;
}

void StateManager::clearScore()
{
	score = 0;
	dead = false;
}

