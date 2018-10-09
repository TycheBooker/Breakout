#pragma once
#include <SFML/Audio.hpp>
#include "BaseObject.h"

class Brick : public BaseObject
{
public:
	Brick(std::string ID, sf::Vector2f position);
	~Brick();

	virtual void update(sf::Time deltaTime);
	sf::FloatRect getGlobalBounds();
	void getHit();
	bool isDestroyed() const;
	unsigned getBreakScore() const;
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void createBrick(std::string ID);

	sf::Sprite brickSprite;
	//sf::Sound hitSound;
	//sf::Sound breakSound;

	std::string ID;
	int hitPoints;
	int breakScore;
};

