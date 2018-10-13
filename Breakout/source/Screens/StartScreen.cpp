#include "Settings.h"
#include "StartScreen.h"
#include "Title.h"
#include "BlinkingLabel.h"

StartScreen::StartScreen(StateManager * stateManager) :
	BaseScreen(stateManager),
	pageMargin(100.f)
{
	createTitle("BREAKOUT");
	createBlinkingLabel("Press Enter to Play!");
}

StartScreen::~StartScreen()
{
	for (auto & itr : pageElements) {
		delete itr;
	}
	pageElements.clear();
}


void StartScreen::renderScreen(sf::RenderWindow &window)
{
	for (auto & element : pageElements) {
		window.draw(*element);
	}
}

void StartScreen::updateScreen(sf::Time deltaTime)
{
	for (auto & element : pageElements) {
		element->update(deltaTime);
	}
}

void StartScreen::handleInput(sf::Event event)
{
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter)) {
		startGame();
	}
}

void StartScreen::createTitle(std::string titleText)
{
	TextElement * title = new Title(titleText);
	title->move(0, pageMargin);
	pageElements.push_back(title);
}

void StartScreen::createBlinkingLabel(std::string labelText)
{
	TextElement * label = new BlinkingLabel(labelText);
	label->centerText();
	float pageElementsHeight = pageMargin;
	for (auto & element : pageElements) {
		pageElementsHeight += element->getSize().y;
		pageElementsHeight += element->getMarginBottom();
	}
	label->move(0, pageElementsHeight);
	pageElements.push_back(label);
}

void StartScreen::startGame()
{
	stateManager->switchScreen(Screen::GameScreen);
}
