#include "Ball.h"
#include "Settings.h"
#include "Paddle.h"
#include "Level.h"

Ball::Ball(Paddle * paddle, std::function<void()> loseLife) :
	ballSprite(AssetManager::getInstance()->getTexture("ball.png")),
	paddle(paddle),
	loseLife(loseLife),
	onStart(true)
{
	setOrigin(ballSprite.getLocalBounds().width / 2.f, ballSprite.getLocalBounds().height / 2.f);
	restartBall();
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
	if (ballBounds.left < 0) {
		velocity.x = ballVelocity;
	}
	else if (ballBounds.left + ballBounds.width > windowWidth) {
		velocity.x = -ballVelocity;
	}
	if (ballBounds.top < 0) {
		velocity.y = ballVelocity;
	}
	else if (ballBounds.top + ballBounds.height > windowHeight) {
		loseLife();
		restartBall();
	}

	if (onStart) {
		setPosition(paddle->getPosition().x, getPosition().y);
	}
}

sf::FloatRect Ball::getGlobalBounds()
{
	return getTransform().transformRect(ballSprite.getLocalBounds());
}

void Ball::startMoving()
{
	velocity = { -ballVelocity, -ballVelocity };
	onStart = false;
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

void Ball::restartBall()
{
	velocity = {0, 0};
	setPosition(windowWidth / 2.f, windowHeight - 100.f - ballSprite.getLocalBounds().height);
	onStart = true;
}
