#pragma once
#include <SFML/Audio.hpp>

class MusicPlayer
{
public:
	MusicPlayer();
	~MusicPlayer();

	void playMusic();
	void stopPlaying();
private:
	sf::Music gameMusic;
};