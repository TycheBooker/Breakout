#include "GameScreen.h"
#include "Settings.h"

GameScreen::GameScreen(StateManager * stateManager) :
	BaseScreen(stateManager),
	paddle(),
	ball(),
	level(),
	gameHUD()
{
	gameObjects.push_back(&paddle);
	gameObjects.push_back(&ball);
	gameObjects.push_back(&level);
}

GameScreen::~GameScreen()
{
}

void GameScreen::renderScreen(sf::RenderWindow & window)
{
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		window.draw(*gameObjects[i]);
	}
	gameHUD.renderHUD(window);
}

void GameScreen::updateScreen(sf::Time deltaTime)
{
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update(deltaTime);
	}
	gameHUD.updateHUD(deltaTime);
	paddle.paddleCollision(ball);
	level.brickCollision(ball);
}

void GameScreen::handleInput(sf::Event event)
{
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
		ball.startMoving();
	}
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter)) {
		finishGame();
	}
}

void GameScreen::finishGame()
{
	stateManager->switchScreen(Screen::EndScreen);
}



