#include "TextElement.h"
#include "Settings.h"

TextElement::TextElement(std::string text) :
	text(text, textFont),
	marginBottom(10.f)
{
}


TextElement::~TextElement()
{
}

sf::Font & TextElement::textFont = AssetManager::getInstance()->getFont("AtariClassic-Regular.ttf");


void TextElement::update(sf::Time deltaTime)
{
}

sf::FloatRect TextElement::getGlobalBounds()
{
	return getTransform().transformRect(text.getLocalBounds());
}

sf::Vector2f TextElement::getSize()
{
	return sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height);
}

float TextElement::getMarginBottom()
{
	return marginBottom;
}

void TextElement::setText(std::string text)
{
	this->text.setString(text);
}

void TextElement::setColor(sf::Color color)
{
	text.setFillColor(color);
}

void TextElement::setCharacterSize(unsigned size)
{
	text.setCharacterSize(size);
}

void TextElement::centerText()
{
	setCenterOrigin();
	setPosition(windowWidth / 2.f, 0);
}

void TextElement::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(text, states);
}

void TextElement::setCenterOrigin()
{
	text.setOrigin({ text.getLocalBounds().width / 2.f, text.getCharacterSize() / 2.f });
}
