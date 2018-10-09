#pragma once
#include "BaseScreen.h"
#include "GameScreen.h"
#include "TextElement.h"

class StartScreen :
	public BaseScreen
{
public:
	StartScreen(StateManager * stateManager);
	~StartScreen();

	virtual void renderScreen(sf::RenderWindow & window);
	virtual void updateScreen(sf::Time deltaTime);
	virtual void handleInput(sf::Event event);
private:
	void createTitle(std::string titleText);
	void createBlinkingLabel(std::string labelText);

	std::vector<TextElement *> pageElements;
	float pageMargin;

	void startGame();
};

