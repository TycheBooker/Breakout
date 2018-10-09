#pragma once
#include <SFML/Graphics.hpp>
#include "BaseObject.h"
#include "TextElement.h"
#include "StateManager.h"

class HUD : public BaseObject
{
public:
	HUD(StateManager * stateManager);
	~HUD();

	virtual void update(sf::Time deltaTime);
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void createLabel(std::string labelText, bool alignLeft);

	TextElement points;
	TextElement lives;
	std::vector <TextElement *> HUDElements;
	float pageMargin;

	StateManager * stateManager;
};

