#include "EndScreen.h"
#include "Title.h"

EndScreen::EndScreen(StateManager * stateManager) :
	BaseScreen(stateManager),
	pageMargin(100.f)
{
	if (stateManager->isDead()) {
		createTitle("You died!");
	}
	else {
		createTitle("GZ! You\nescaped!");
	}
	std::string scoreText = "Your score: " + std::to_string(stateManager->getScore());
	createLabel(scoreText);
	createLabel("Play again?");
	createLabel("Y/N");
}

EndScreen::~EndScreen()
{
	for (auto & itr : pageElements) {
		delete itr;
	}
	pageElements.clear();
}

void EndScreen::renderScreen(sf::RenderWindow & window)
{
	for (auto & element : pageElements) {
		window.draw(*element);
	}
}

void EndScreen::updateScreen(sf::Time deltaTime)
{
}

void EndScreen::handleInput(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Y) {
			restartGame();
		}
		else if (event.key.code == sf::Keyboard::N) {
			stateManager->getWindow()->close();
		}
	}
}

void EndScreen::createTitle(std::string titleText)
{
	TextElement * title = new Title(titleText);
	title->move(0, pageMargin);
	pageElements.push_back(title);
}

void EndScreen::createLabel(std::string labelText)
{
	TextElement * label = new TextElement(labelText);
	label->centerText();
	float pageElementsHeight = pageMargin;
	for (auto & element : pageElements) {
		pageElementsHeight += element->getSize().y;
		pageElementsHeight += element->getMarginBottom();
	}
	label->move(0, pageElementsHeight);
	pageElements.push_back(label);
}

void EndScreen::restartGame()
{
	stateManager->clearScore();
	stateManager->switchScreen(Screen::StartScreen);
}