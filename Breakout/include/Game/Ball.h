#pragma once
#include "BaseObject.h"

class Paddle;
class Level;

class Ball : public BaseObject
{
public:
	Ball();
	~Ball();

	virtual void update(sf::Time deltaTime);
	virtual sf::FloatRect getGlobalBounds();

	void startMoving();
	void setVelocity(sf::Vector2f velocity);
	sf::Vector2f velocity;
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	sf::Sprite ballSprite;
};

