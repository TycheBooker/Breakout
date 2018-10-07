#pragma once
#include "BaseScreen.h"
#include "StartScreen.h"
#include "TextElement.h"

class EndScreen :
	public BaseScreen
{
public:
	EndScreen(StateManager * stateManager);
	~EndScreen();

	virtual void renderScreen(sf::RenderWindow & window);
	virtual void updateScreen(sf::Time deltaTime);
	virtual void handleInput(sf::Event event);
private:
	void createTitle(std::string titleText);
	void createLabel(std::string labelTxt);

	std::vector<TextElement *> pageElements;
	float pageMargin;

	void restartGame();
};