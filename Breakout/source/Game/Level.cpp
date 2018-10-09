#include <algorithm>
#include "Level.h"
#include "Settings.h"

constexpr int rowCount = 3;
constexpr int columnCount = 20;
constexpr int rowSpacing = 3;
constexpr int columnSpacing = 3;
constexpr int brickWidth = 32;
constexpr int brickHeight = 16;

Level::Level(std::function<void(int)> increaseScore) :
	increaseScore(increaseScore)
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

void Level::brickCollision(Ball & ball)
{
	sf::FloatRect ballBounds = ball.getGlobalBounds();

	for (auto & brick : bricks) {
		sf::FloatRect brickBounds = brick->getGlobalBounds();

		if (!brickBounds.intersects(ballBounds)) continue;
		brick->getHit();

		// intersection amount by directions
		float intersectLeft = ballBounds.left + ballBounds.width  - brickBounds.left;
		float intersectRight = brickBounds.left + brickBounds.width - ballBounds.left;
		float intersectTop = ballBounds.top + ballBounds.height - brickBounds.top;
		float intersectBottom = brickBounds.top + brickBounds.height - ballBounds.top;

		// hit direction by axis
		bool hitLeft(abs(intersectLeft) < abs(intersectRight));
		bool hitTop(abs(intersectTop) < abs(intersectBottom));

		// intersection amount by axis
		float intersectX = hitLeft ? intersectLeft : intersectRight;
		float intersectY = hitTop ? intersectTop : intersectBottom;

		// change velocity by hit direction
		if (abs(intersectX) < abs(intersectY))
			ball.velocity.x = hitLeft ? -ballVelocity : ballVelocity;
		else
			ball.velocity.y = hitTop ? -ballVelocity : ballVelocity;
	}
	
	evaluateBricks();
}

bool Level::isFinnished()
{
	return bricks.size() == 0;
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

void Level::evaluateBricks()
{
	bricks.erase(
		std::remove_if(
			bricks.begin(),
			bricks.end(),
			[this](const Brick * brick) -> bool {
				if (brick->isDestroyed()) {
					increaseScore(brick->getBreakScore());
					return true;
				}
			}
		),
		bricks.end()
	);
}
