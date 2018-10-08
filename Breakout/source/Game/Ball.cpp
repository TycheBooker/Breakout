#include "Ball.h"
#include "Settings.h"
#include "Paddle.h"
#include "Level.h"

Ball::Ball() :
	ballSprite(AssetManager::getInstance()->getTexture("ball.png")),
	velocity(0, 0)
{
	setOrigin(ballSprite.getLocalBounds().width / 2.f, ballSprite.getLocalBounds().height / 2.f);
	setPosition(windowWidth / 2.f, windowHeight - 100.f - ballSprite.getLocalBounds().height);
}

Ball::~Ball()
{
}

void Ball::update(sf::Time deltaTime)
{
	move(velocity);

	sf::FloatRect ballBounds = {
		getPosition().x - ballSprite.getLocalBounds().width / 2.f,
		getPosition().y - ballSprite.getLocalBounds().height / 2.f,
		ballSprite.getLocalBounds().width / 2.f,
		ballSprite.getLocalBounds().height / 2.f,
	};
	if (ballBounds.left < 0) velocity.x = ballVelocity;
	else if (ballBounds.left + ballBounds.width > windowWidth)
		velocity.x = -ballVelocity;
	if (ballBounds.top < 0)
		velocity.y = ballVelocity;
	// remove bottom;
	else if (ballBounds.top + ballBounds.height > windowHeight)
		velocity.y = -ballVelocity;

	if (velocity.y == 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) &&
			getPosition().x - ballSprite.getLocalBounds().width / 2.f > 0) {
			velocity.x = -paddleVelocity;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&
			getPosition().x + ballSprite.getLocalBounds().width / 2.f < windowWidth) {
			velocity.x = paddleVelocity;
		}
		else {
			velocity.x = 0;
		}
	}
}

sf::FloatRect Ball::getGlobalBounds()
{
	return getTransform().transformRect(ballSprite.getLocalBounds());
}

void Ball::startMoving()
{
	velocity = { -ballVelocity, -ballVelocity };
}

void Ball::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void Ball::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(ballSprite, states);
}
