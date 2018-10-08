#pragma once
#include <SFML\Graphics.hpp>
#include "BaseObject.h"
#include "Brick.h"
#include "Ball.h"

class Level : public BaseObject
{
public:
	Level();
	~Level();

	virtual void update(sf::Time deltaTime);
	virtual sf::FloatRect getGlobalBounds();
	void brickCollision(Ball & ball);
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void loadLevel();

	std::vector<Brick *> bricks;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
};

