#include <algorithm>
#include <iostream>
#include "Level.h"
#include "Settings.h"

Level::Level(std::function<void(int)> increaseScore) :
	increaseScore(increaseScore),
	nextLevel()
{
	loadLevel("Assets/Data/Level1.xml");
}

Level::~Level()
{
	for (auto & itr : bricks) {
		delete itr;
	}
	bricks.clear();
	for (auto & itr : brickTypes) {
		delete itr.second;
	}
	brickTypes.clear();
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
		if (abs(intersectX) < abs(intersectY)) {
			ball.velocity.x = hitLeft ? -ballVelocity : ballVelocity;
		}
		else {
			ball.velocity.y = hitTop ? -ballVelocity : ballVelocity;
		}
	}

	evaluateBricks();
}

bool Level::loadNext()
{
	if (nextLevel.size() == 0) return false;

	loadLevel(nextLevel);
	return true;
}

bool Level::isFinnished()
{
	if (bricks.size() == 0) return true;

	for (auto & brick : bricks) {
		if (!brick->isImpenetrable()) return false;
	}
	return true;
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
	doc.LoadFile(levelPath.c_str());

	if (doc.ErrorID()) {
		std::cerr << "Failed loading the path file: " << levelPath << " !" << std::endl;
		return;
	}

	tinyxml2::XMLElement * level = doc.FirstChildElement("Level");

	setLevelAttributes(level);
	createBrickTypes(level);
	createBricks(level);
}

void Level::setLevelAttributes(tinyxml2::XMLElement * level)
{
	const char * backgroundTexture = nullptr;
	const char * nextLevel = nullptr;

	level->QueryIntAttribute("RowCount", &rowCount);
	level->QueryIntAttribute("ColumnCount", &columnCount);
	level->QueryIntAttribute("RowSpacing", &rowSpacing);
	level->QueryIntAttribute("ColumnSpacing", &columnSpacing);
	level->QueryStringAttribute("BackgroundTexture", &backgroundTexture);
	level->QueryIntAttribute("BrickWidth", &brickWidth);
	level->QueryIntAttribute("BrickHeight", &brickHeight);
	level->QueryStringAttribute("NextLevel", &nextLevel);

	if (backgroundTexture != nullptr) {
		this->backgroundTexture = AssetManager::getInstance()->getTexture(backgroundTexture);
		background.setTexture(&this->backgroundTexture);
	}
	if (nextLevel != nullptr) {
		this->nextLevel = { nextLevel };
	}
	else {
		this->nextLevel = {};
	}
}

void Level::createBrickTypes(tinyxml2::XMLElement * level)
{
	tinyxml2::XMLElement * xmlBrickTypes = level->FirstChildElement("BrickTypes");
	for (auto * xmlBrickType = xmlBrickTypes->FirstChildElement("BrickType"); xmlBrickType; xmlBrickType = xmlBrickType->NextSiblingElement("BrickType")) {
		const char * ID = "";
		int hitPoints = 0;
		int breakScore = 0;
		const char * texture = "";
		const char * hitSound = "";
		const char * breakSound = "";

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

	for (float i = 0; i < rowCount; i++) {
		for (float y = 0; y < columnCount; y++) {
			if (brickCount == brickLayout.end()) {
				std::cerr << "There are more bricks in the layout than defined in the level attributes!" << std::endl;
				return;
			}

			// skip brick generation if _ in layout
			if (*brickCount == '_') {
				++brickCount;
				continue;
			}

			// find brick type by Id in layout
			auto brickTypeItr = this->brickTypes.find(*brickCount);
			if (brickTypeItr == this->brickTypes.end()) {
				std::cerr << "Undefined brick type found in bricks!" << std::endl;
				return;
			}

			sf::Vector2f position = { margin + y * brickWidth + y * columnSpacing, margin + i * brickHeight + i * rowSpacing };
			Brick * brick = new Brick(brickTypeItr->second, position);

			bricks.push_back(brick);
			++brickCount;
		}
	}
}

tinyxml2::XMLError Level::
checkXMLResult(tinyxml2::XMLError result)
{
	if (result != tinyxml2::XML_SUCCESS) {
		std::cerr << "Error while reading xml: " << result << " !" << std::endl;
	}
	return result;
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
