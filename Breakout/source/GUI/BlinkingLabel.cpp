#include "BlinkingLabel.h"

BlinkingLabel::BlinkingLabel(std::string text) :
	TextElement(text),
	elapsedTime(sf::Time::Zero),
	blinkTime(sf::seconds(0.5f))
{
}

BlinkingLabel::~BlinkingLabel()
{
}

void BlinkingLabel::update(sf::Time deltaTime)
{
	elapsedTime += deltaTime;
	if (elapsedTime >= blinkTime) {
		toggleVisibility();
		elapsedTime = sf::Time::Zero;
	}
}

void BlinkingLabel::toggleVisibility()
{
	if (text.getFillColor() == sf::Color::White) {
		text.setFillColor(sf::Color::Transparent);
	}
	else {
		text.setFillColor(sf::Color::White);
	}
}
