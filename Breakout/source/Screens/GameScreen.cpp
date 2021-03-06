#include "GameScreen.h"
#include "Settings.h"

GameScreen::GameScreen(StateManager * stateManager) :
	BaseScreen(stateManager),
	paddle(),
	ball(& paddle, std::bind(&GameScreen::loseLife, this)),
	level(std::bind(&GameScreen::increaseScore, this, std::placeholders::_1)),
	gameHUD(stateManager)
{
	gameObjects.push_back(&level);
	gameObjects.push_back(&paddle);
	gameObjects.push_back(&ball);
	gameObjects.push_back(&gameHUD);
}

GameScreen::~GameScreen()
{
}

void GameScreen::renderScreen(sf::RenderWindow & window)
{
	for (auto & object : gameObjects) {
		window.draw(*object);
	}
}

void GameScreen::updateScreen(sf::Time deltaTime)
{
	for (auto & object : gameObjects) {
		object->update(deltaTime);
	}
	paddle.paddleCollision(ball);
	level.brickCollision(ball);
	if (level.isFinnished() && !level.loadNext()) {
		finishGame();
	}
}

void GameScreen::handleInput(sf::Event event)
{
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
		ball.startMoving();
	}
	// testing purposes
	//if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter)) {
	//	finishGame();
	//}
}

void GameScreen::loseLife()
{
	stateManager->loseLife();
	if (stateManager->isDead()) {
		finishGame();
	}
}

void GameScreen::increaseScore(int points)
{
	stateManager->increaseScore(points);
}

void GameScreen::finishGame()
{
	stateManager->switchScreen(Screen::EndScreen);
}



