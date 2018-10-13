#pragma once
#include <functional>
#include "BaseObject.h"

class Paddle;
class Level;

class Ball : public BaseObject
{
public:
	Ball(Paddle * paddle, std::function<void()> loseLife);
	~Ball();

	virtual void update(sf::Time deltaTime);
	sf::FloatRect getGlobalBounds();

	void startMoving();
	void setVelocity(sf::Vector2f velocity);
	sf::Vector2f velocity;
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void restartBall();
	std::function<void()> loseLife;

	Paddle * paddle;
	sf::Sprite ballSprite;
	bool onStart;
};

