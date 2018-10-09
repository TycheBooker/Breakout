#pragma once
#include "TextElement.h"

class BlinkingLabel : public TextElement
{
public:
	BlinkingLabel(std::string text);
	~BlinkingLabel();

	virtual void update(sf::Time deltaTime);
private:
	void toggleVisibility();

	sf::Time elapsedTime;
	sf::Time blinkTime;
};

