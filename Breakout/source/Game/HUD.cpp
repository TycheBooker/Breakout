#include "HUD.h"
#include "Settings.h"

HUD::HUD(StateManager * stateManager) :
	stateManager(stateManager),
	points(std::to_string(stateManager->getScore())),
	lives(std::to_string(stateManager->getLives())),
	pageMargin(50.f)
{
	createLabel("Points:", false);
	createLabel("Lives:", true);	
	points.setPosition(windowWidth - pageMargin - points.getSize().x - 100.f, windowHeight - pageMargin);
	lives.setPosition(pageMargin, windowHeight - pageMargin);
	HUDElements.push_back(&points);
	HUDElements.push_back(&lives);
}

HUD::~HUD()
{
}

void HUD::update(sf::Time deltaTime)
{
	for (auto & element : HUDElements) {
		element->update(deltaTime);
	}
	if (points.getText() != std::to_string(stateManager->getScore())) {
		points.setText(std::to_string(stateManager->getScore()));
	}
	if (lives.getText() != std::to_string(stateManager->getLives())) {
		lives.setText(std::to_string(stateManager->getLives()));
	}
}

void HUD::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (auto & element : HUDElements) {
		target.draw(*element, states);
	}
}

void HUD::createLabel(std::string labelText, bool alignLeft)
{
	TextElement * label = new TextElement(labelText);
	sf::Vector2f position;
	if (alignLeft) {
		position = { pageMargin, windowHeight - pageMargin - label->getSize().y - label->getMarginBottom() };
	}
	else {
		position = { windowWidth - pageMargin - label->getSize().x, windowHeight - pageMargin - label->getSize().y - label->getMarginBottom() };
	}
	label->setPosition(position);
	HUDElements.push_back(label);
}
