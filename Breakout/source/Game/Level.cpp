#include "Level.h"
#include "Settings.h"
#include <iostream>

constexpr int rowCount = 3;
constexpr int columnCount = 20;
constexpr int rowSpacing = 3;
constexpr int columnSpacing = 3;
constexpr int brickWidth = 32;
constexpr int brickHeight = 16;

Level::Level()
{
	loadLevel();
}

Level::~Level()
{
}

void Level::update(sf::Time deltaTime)
{
	for (auto & brick : bricks) {
		brick->update(deltaTime);
	}
}

sf::FloatRect Level::getGlobalBounds()
{
	return sf::FloatRect();
}

void Level::brickCollision(Ball & ball)
{
	for (auto & brick : bricks) {
		if (!brick->getGlobalBounds().intersects(ball.getGlobalBounds())) continue;
		brick->getHit();
	}

	//bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));

	//// We can apply the same idea for top/bottom collisions.
	//bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	//// Let's store the minimum overlaps for the X and Y axes.
	//float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	//float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

	//// If the magnitude of the X overlap is less than the magnitude
	//// of the Y overlap, we can safely assume the ball hit the brick
	//// horizontally - otherwise, the ball hit the brick vertically.

	//// Then, upon our assumptions, we change either the X or Y velocity
	//// of the ball, creating a "realistic" response for the collision.
	//if (abs(minOverlapX) < abs(minOverlapY))
	//	mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
	//else
	//	mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
}

void Level::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(background, states);
	for (auto & brick : bricks) {
		target.draw(*brick, states);
	}
}

void Level::loadLevel()
{
	backgroundTexture = AssetManager::getInstance()->getTexture("");
	background.setTexture(&backgroundTexture);
	float margin = (windowWidth - ((brickWidth + rowSpacing) * columnCount - rowSpacing)) / 2.f;
	for (float i = 0; i < columnCount; i++)
	{
		for (float y = 0; y < rowCount; y++)
		{
			sf::Vector2f position = { margin + i * brickWidth + i * rowSpacing, margin + y * brickHeight + y * columnSpacing };
			Brick * brick = new Brick("S", position);
			bricks.push_back(brick);
		}
	}
}
