#include <algorithm>
#include "Level.h"
#include "Settings.h"
#include <iostream>

Level::Level(std::function<void(int)> increaseScore) :
	increaseScore(increaseScore)
{
	loadLevel("assets/data/Level1");
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
		float intersectLeft = ballBounds.left + ballBounds.width - brickBounds.left;
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

void Level::loadLevel(std::string levelPath)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("assets/Data/Level1.xml");
	tinyxml2::XMLElement * level = doc.FirstChildElement("Level");

	setLevelAttributes(level);
	createBrickTypes(level);
	createBricks(level);

	//return doc.ErrorID();
}

void Level::setLevelAttributes(tinyxml2::XMLElement * level)
{
	const char * backgroundTexture;

	level->QueryIntAttribute("RowCount", &rowCount);
	level->QueryIntAttribute("ColumnCount", &columnCount);
	level->QueryIntAttribute("RowSpacing", &rowSpacing);
	level->QueryIntAttribute("ColumnSpacing", &columnSpacing);
	level->QueryStringAttribute("BackgroundTexture", &backgroundTexture);

	this->backgroundTexture = AssetManager::getInstance()->getTexture(backgroundTexture);
	background.setTexture(&this->backgroundTexture);
}

void Level::createBrickTypes(tinyxml2::XMLElement * level)
{
	tinyxml2::XMLElement * xmlBrickTypes = level->FirstChildElement("BrickTypes");
	for (auto * xmlBrickType = xmlBrickTypes->FirstChildElement("BrickType"); xmlBrickType; xmlBrickType = xmlBrickType->NextSiblingElement("BrickType")) {
		const char * ID;
		int hitPoints;
		int breakScore;
		const char * texture;
		const char * hitSound;
		const char * breakSound;

		xmlBrickType->QueryStringAttribute("Id", &ID);
		xmlBrickType->QueryIntAttribute("HitPoints", &hitPoints);
		xmlBrickType->QueryIntAttribute("BreakScore", &breakScore);
		xmlBrickType->QueryStringAttribute("Texture", &texture);
		xmlBrickType->QueryStringAttribute("HitSound", &hitSound);
		xmlBrickType->QueryStringAttribute("BreakSound", &breakSound);

		BrickType * brickType = new BrickType(ID[0], hitPoints, breakScore, texture, hitSound, breakSound);
		brickTypes.emplace(ID[0], brickType);
	}
}

void Level::createBricks(tinyxml2::XMLElement * level)
{
	tinyxml2::XMLElement* xmlBricks = level->FirstChildElement("Bricks");
	std::string brickLayout = { xmlBricks->GetText() };
	brickLayout.erase(std::remove_if(brickLayout.begin(), brickLayout.end(), ::isspace), brickLayout.end());

	float margin = (windowWidth - ((brickWidth + rowSpacing) * columnCount - rowSpacing)) / 2.f;
	auto brickCount = brickLayout.begin();

	for (float i = 0; i < rowCount; i++)
	{
		for (float y = 0; y < columnCount; y++)
		{
			if (brickCount == brickLayout.end()) {
				return; // too many bricks
			}

			// find brick type by Id in layout
			auto brickTypeItr = this->brickTypes.find(*brickCount);
			if (brickTypeItr == this->brickTypes.end()) {
				return; // brick type not found
			}

			sf::Vector2f position = { margin + y * brickWidth + y * columnSpacing, margin + i * brickHeight + i * rowSpacing };
			Brick * brick = new Brick(brickTypeItr->second, position);

			bricks.push_back(brick);
			++brickCount;
		}
	}
}

void Level::evaluateBricks()
{
	bricks.erase(std::remove_if(bricks.begin(), bricks.end(),
		[this](const Brick * brick) -> bool {
		if (brick->isDestroyed()) {
			increaseScore(brick->getBreakScore());
			return true;
		}
		return false;
	}
	),
		bricks.end()
		);
}
