#include "Brick.h"

Brick::Brick(std::string ID, sf::Vector2f position) :
	ID(ID)
{
	createBrick(ID);
	setPosition(position);
}

Brick::~Brick()
{
}

void Brick::update(sf::Time deltaTime)
{
}

sf::FloatRect Brick::getGlobalBounds()
{
	return getTransform().transformRect(brickSprite.getLocalBounds());
}

void Brick::getHit()
{
	hitPoints--;
	if (hitPoints == 0) {
		// play break sound
	}
	else {
		// play hit sound
	}
}

bool Brick::isDestroyed() const
{
	return hitPoints <= 0;
}

unsigned Brick::getBreakScore() const
{
	return breakScore;
}

void Brick::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(brickSprite, states);
}

void Brick::createBrick(std::string ID)
{
	brickSprite.setTexture(AssetManager::getInstance()->getTexture("soft.png"));
	hitPoints = 1;
	breakScore = 50;
}
