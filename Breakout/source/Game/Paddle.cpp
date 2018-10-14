#include "Paddle.h"
#include "Settings.h"

Paddle::Paddle() :
	paddleSprite(AssetManager::getInstance()->getTexture("paddle.png")),
	velocity(0, 0)
{
	setOrigin(paddleSprite.getLocalBounds().width / 2.f, paddleSprite.getLocalBounds().height / 2.f);
	setPosition(windowWidth / 2.f, windowHeight - 100.f);
}

Paddle::~Paddle()
{
}

void Paddle::update(sf::Time deltaTime)
{
	move(velocity);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) &&
		getPosition().x - paddleSprite.getLocalBounds().width / 2.f > 0) {
		velocity.x = -paddleVelocity;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&
		getPosition().x + paddleSprite.getLocalBounds().width / 2.f < windowWidth) {
		velocity.x = paddleVelocity;
	}
	else {
		velocity.x = 0;
	}
}

sf::FloatRect Paddle::getGlobalBounds()
{
	return getTransform().transformRect(paddleSprite.getLocalBounds());
}

void Paddle::paddleCollision(Ball & ball)
{
	sf::FloatRect ballBounds = ball.getGlobalBounds();
	sf::FloatRect paddleBounds = getGlobalBounds();
	if (!paddleBounds.intersects(ballBounds)) return;

	float intersectTop = ballBounds.top + ballBounds.height - paddleBounds.top;
	float intersectBottom = paddleBounds.top + paddleBounds.height - ballBounds.top;

	if (abs(intersectTop) > abs(intersectBottom)) return;      // don't count bottom hit

	ball.velocity.y = -ballVelocity;

	// different bounce direction for left and right paddle sides
	if (getPosition().x < ball.getPosition().x) {
		ball.velocity.x = ballVelocity;
	}
	else {
		ball.velocity.x = -ballVelocity;
	}
}

void Paddle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(paddleSprite, states);
}
