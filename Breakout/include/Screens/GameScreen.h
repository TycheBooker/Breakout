#pragma once
#include "BaseScreen.h"
#include "BaseObject.h"
#include "HUD.h"
#include "Level.h"
#include "Paddle.h"
#include "Ball.h"
#include "Level.h"

class GameScreen : public BaseScreen
{
public:
	GameScreen(StateManager * stateManager);
	~GameScreen();

	virtual void renderScreen(sf::RenderWindow & window);
	virtual void updateScreen(sf::Time deltaTime);
	virtual void handleInput(sf::Event event);
private:
	void loseLife();
	void increaseScore(int points);
	void finishGame();

	HUD gameHUD;
	Level level;
	Paddle paddle;
	Ball ball;

	std::vector<BaseObject *> gameObjects;
};