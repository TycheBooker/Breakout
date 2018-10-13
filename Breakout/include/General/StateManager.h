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
	void cleanState();
	void clearScore();
	void loseLife();
	void increaseScore(int points);
	int getScore();
	int getLives();
	bool isDead();

	BaseScreen * getCurrentScreen();
	sf::RenderWindow * getWindow();

private:
	BaseScreen * currentScreen;
	BaseScreen * nextScreen;
	sf::RenderWindow * window;

	int score;
	int lives;
};

