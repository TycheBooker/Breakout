#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() :
	gameMusic()
{
	gameMusic.openFromFile("assets/Music/251461__joshuaempyre__arcade-music-loop.wav");
	gameMusic.setLoop(true);
	gameMusic.setVolume(20);
}

MusicPlayer::~MusicPlayer()
{
}

void MusicPlayer::playMusic()
{
	gameMusic.play();
}