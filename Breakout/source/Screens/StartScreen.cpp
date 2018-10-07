#include "Settings.h"
#include "StartScreen.h"
#include "Title.h"

StartScreen::StartScreen(StateManager * stateManager) :
	BaseScreen(stateManager),
	pageMargin(100.f)
{
	createTitle("BREAKOUT");
	createLabel("Press Enter to Play!");
}

StartScreen::~StartScreen()
{
	for (size_t i = 0; i < pageElements.size(); i++)
	{
		delete pageElements[i];
	}
	pageElements.clear();
}


void StartScreen::renderScreen(sf::RenderWindow &window)
{
	for (size_t i = 0; i < pageElements.size(); i++)
	{
		window.draw(*pageElements[i]);
	}
}

void StartScreen::updateScreen(sf::Time deltaTime)
{
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

void StartScreen::createLabel(std::string labelText)
{
	TextElement * label = new TextElement(labelText);
	label->centerText();
	float pageElementsHeight = pageMargin;
	for (size_t i = 0; i < pageElements.size(); i++)
	{
		pageElementsHeight += pageElements[i]->getSize().y;
		pageElementsHeight += pageElements[i]->getMarginBottom();
	}
	label->move(0, pageElementsHeight);
	pageElements.push_back(label);
}

void StartScreen::startGame()
{
	stateManager->switchScreen(Screen::GameScreen);
}
