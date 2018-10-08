#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"

class BaseObject : public sf::Drawable, public sf::Transformable
{
public:
	BaseObject();
	virtual ~BaseObject();

	virtual void update(sf::Time deltaTime) = 0;
	virtual sf::FloatRect getGlobalBounds() = 0;
protected:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;
};