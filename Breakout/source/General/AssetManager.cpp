#include "AssetManager.h"
#include "Settings.h"

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
	delete singletonInstance;
}

AssetManager * AssetManager::singletonInstance;

AssetManager * AssetManager::getInstance()
{
	if (singletonInstance == NULL) {
		singletonInstance = new AssetManager();
	}
	return singletonInstance;
}

sf::Texture & AssetManager::getTexture(std::string const & filename)
{
	std::map<std::string, sf::Texture> & textureMap = singletonInstance->managerTextures;

	std::map<std::string, sf::Texture>::iterator pairFound = textureMap.find(filename);
	if (pairFound != textureMap.end()) {
		return pairFound->second;
	}
	else {
		sf::Texture & texture = textureMap[filename];
		texture.loadFromFile(graphicsPath + filename);
		return texture;
	}
}

sf::Font & AssetManager::getFont(std::string const & filename)
{
	std::map<std::string, sf::Font> & fontMap = singletonInstance->managerFonts;

	std::map<std::string, sf::Font>::iterator pairFound = fontMap.find(filename);
	if (pairFound != fontMap.end()) {
		return pairFound->second;
	}
	else {
		sf::Font & font = fontMap[filename];
		font.loadFromFile(fontsPath + filename);
		return font;
	}
}

sf::SoundBuffer & AssetManager::getSoundBuffer(std::string const & filename)
{
	std::map<std::string, sf::SoundBuffer> & soundBufferMap = singletonInstance->managerSoundBuffers;

	std::map<std::string, sf::SoundBuffer>::iterator pairFound = soundBufferMap.find(filename);
	if (pairFound != soundBufferMap.end()) {
		return pairFound->second;
	}
	else {
		sf::SoundBuffer & soundBuffer = soundBufferMap[filename];
		soundBuffer.loadFromFile(audioPath + filename);
		return soundBuffer;
	}
}