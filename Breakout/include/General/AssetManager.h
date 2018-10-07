#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetManager
{
public:
	static AssetManager * getInstance();
	static sf::Texture & getTexture(std::string const & filename);
	static sf::Font & getFont(std::string const & filename);
	static sf::SoundBuffer & getSoundBuffer(std::string const & filename);

private:
	AssetManager();
	~AssetManager();

	std::map<std::string, sf::Texture> managerTextures;
	std::map<std::string, sf::Font> managerFonts;
	std::map<std::string, sf::SoundBuffer> managerSoundBuffers;
	static AssetManager * singletonInstance;
};


