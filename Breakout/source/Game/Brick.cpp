#include "Brick.h"

Brick::Brick(BrickType * brickType, sf::Vector2f position) :
	brickType(brickType),
	hitPoints(brickType->hitPoints)
{
	brickSprite.setTexture(brickType->texture);
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
	if (hitPoints < 0) return;

	hitPoints--;
	if (brickType->hitPoints == 0) {
		brickType->breakSound.play();
	}
	else {
		brickType->hitSound.play();
	}
}

bool Brick::isDestroyed() const
{
	return hitPoints == 0;
}

bool Brick::isImpenetrable()
{
	return hitPoints < 0;
}

unsigned Brick::getBreakScore() const
{
	return brickType->breakScore;
}

void Brick::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(brickSprite, states);
}

