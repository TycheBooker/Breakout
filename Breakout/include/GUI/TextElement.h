#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"

class TextElement : public sf::Drawable, public sf::Transformable
{
public:
	TextElement(std::string text);
	virtual ~TextElement();

	virtual void update(sf::Time deltaTime);
	virtual sf::Vector2f getSize();
	virtual float getMarginBottom();

	virtual void setText(std::string text);
	virtual void setColor(sf::Color color);
	virtual void setCharacterSize(unsigned size);
	virtual void centerText();
protected:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void setCenterOrigin();

	static sf::Font & textFont;

	sf::Text text;
	float marginBottom;
};