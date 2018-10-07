#pragma once
#include <SFML/Graphics.hpp>

class BaseScreen;

enum class Screen
{
	StartScreen,
	GameScreen,
	EndScreen
};

class StateManager
{
public:
	StateManager(sf::RenderWindow * window);
	~StateManager();

	void switchScreen(Screen newScreen);
	void clearScore();

	int getScore();
	bool isDead();

	BaseScreen * getCurrentScreen();
	sf::RenderWindow * getWindow();

private:
	BaseScreen * currentScreen;
	BaseScreen * nextScreen;
	sf::RenderWindow * window;

	int score;
	bool dead;
};

