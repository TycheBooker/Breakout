#pragma once
#include "BaseObject.h"
#include "Ball.h"

class Paddle :	public BaseObject
{
public:
	Paddle();
	~Paddle();

	virtual void update(sf::Time deltaTime);
	virtual sf::FloatRect getGlobalBounds();

	void paddleCollision(Ball & ball);
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	sf::Sprite paddleSprite;
	sf::Vector2f velocity;

};

