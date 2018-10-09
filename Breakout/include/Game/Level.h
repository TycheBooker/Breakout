#pragma once
#include <SFML\Graphics.hpp>
#include "BaseObject.h"
#include "Brick.h"
#include "Ball.h"

class Level : public BaseObject
{
public:
	Level(std::function<void(int)> increaseScore);
	~Level();

	virtual void update(sf::Time deltaTime);

	void brickCollision(Ball & ball);
	bool isFinnished();
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void loadLevel();
	void evaluateBricks();
	std::function<void(int)> increaseScore;

	std::vector<Brick *> bricks;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
};

