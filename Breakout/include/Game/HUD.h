#pragma once
#include <SFML/Graphics.hpp>

class HUD
{
public:
	HUD();
	~HUD();

	void renderHUD(sf::RenderWindow & window);
	void updateHUD(sf::Time deltaTime);
};

