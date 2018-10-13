#pragma once
#include <SFML/Audio.hpp>
#include "BaseObject.h"

struct BrickType {
	BrickType(char ID, int hitPoints, int breakScore, std::string texturePath, std::string hitSound, std::string breakSound) :
		ID(ID),
		hitPoints(hitPoints),
		breakScore(breakScore),
		texture(AssetManager::getInstance()->getTexture(texturePath)),
		hitSound(AssetManager::getInstance()->getSoundBuffer(hitSound)),
		breakSound(AssetManager::getInstance()->getSoundBuffer(breakSound))
	{}

	const char ID;
	const int hitPoints;
	const int breakScore;
	sf::Texture texture;
	sf::Sound hitSound;
	sf::Sound breakSound;
};

class Brick : public BaseObject
{
public:
	Brick(BrickType * brickType, sf::Vector2f position);
	~Brick();

	virtual void update(sf::Time deltaTime);
	sf::FloatRect getGlobalBounds();
	void getHit();
	bool isDestroyed() const;
	unsigned getBreakScore() const;
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	BrickType * brickType;
	sf::Sprite brickSprite;
	int hitPoints;
};

