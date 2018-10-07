#include "GameScreen.h"
#include "Settings.h"

GameScreen::GameScreen(StateManager * stateManager) :
	BaseScreen(stateManager)
{
}

GameScreen::~GameScreen()
{
}

void GameScreen::renderScreen(sf::RenderWindow & window)
{
	//tableBorder->renderTableBorder(window);
}

void GameScreen::updateScreen(sf::Time deltaTime)
{
	//tableBorder->updateTableBorder(deltaTime);
}

void GameScreen::handleInput(sf::Event event)
{
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter)) {
		finishGame();
	}
}

void GameScreen::finishGame()
{
	stateManager->switchScreen(Screen::EndScreen);
}



