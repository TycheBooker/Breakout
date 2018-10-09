#pragma once
#include "BaseObject.h"
#include "AssetManager.h"

class TextElement : public BaseObject
{
public:
	TextElement(std::string text);
	virtual ~TextElement();

	virtual void update(sf::Time deltaTime);
	virtual sf::FloatRect getGlobalBounds();
	virtual sf::Vector2f getSize();
	virtual float getMarginBottom();
	virtual std::string getText();

	virtual void setText(std::string text);
	virtual void setCharacterSize(unsigned size);
	virtual void centerText();
protected:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void setCenterOrigin();

	static sf::Font & textFont;

	sf::Text text;
	float marginBottom;
};