#pragma once
#include <unordered_map>
#include <tinyxml2.h>
#include <SFML\Graphics.hpp>
#include "BaseObject.h"
#include "Brick.h"
#include "Ball.h"

using BrickTypes = std::unordered_map<char, BrickType *>;

class Level : public BaseObject
{
public:
	Level(std::function<void(int)> increaseScore);
	~Level();

	virtual void update(sf::Time deltaTime);

	void brickCollision(Ball & ball);
	bool loadNext();
	bool isFinnished();
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void loadLevel(std::string levelPath);
	void setLevelAttributes(tinyxml2::XMLElement * level);
	void createBrickTypes(tinyxml2::XMLElement * level);
	void createBricks(tinyxml2::XMLElement * level);
	tinyxml2::XMLError checkXMLResult(tinyxml2::XMLError result);

	void evaluateBricks();
	std::function<void(int)> increaseScore;

	std::vector<Brick *> bricks;
	BrickTypes brickTypes;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	int brickWidth;
	int brickHeight;
	std::string nextLevel;
};

