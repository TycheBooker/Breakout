#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() :
	gameMusic()
{
	gameMusic.openFromFile("assets/Music/BreakoutMusic.wav");
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

void MusicPlayer::stopPlaying()
{
	gameMusic.stop();
}
