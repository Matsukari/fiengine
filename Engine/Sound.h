#pragma once
#define SOUND_H
#define MUSIC_INFINITE -1

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>

namespace Engine
{

class Sound
{
public:
	Sound(const char* p_path);
	Sound();
	~Sound();

	// Loads WAVE, AIFF, RIFF, OGG, and VOC files.
	bool Load(const char* p_path);
	bool Load(std::string p_path);

	void Play(int channel = -1, int p_loops = 0);
	void Play_Timed(int p_ticks, int p_loops = 0);

	// UP to 128(MIX_MAX_VOLUME)
	void Set_Volume(int p_volume);

	void Destroy();

public:
	int 		id   { 0      };
	std::string path { "None" };

	static const std::string DEFAULT_SOUND;
	static int 	             created_sounds;

private:
	Mix_Chunk*  m_sound = nullptr;
};



class Music
{
public:
	Music(const char* p_path);
	Music();
	~Music();

	// Loads WAVE, MOD, MIDI, OGG, MP3, FLAC files.
	bool Load(const char* p_path);
	bool Load(std::string p_path);

	void Play(int p_loops = 0);

	// UP to 128(MIX_MAX_VOLUME)
	void Set_Volume(int p_volume);
	void Pause();
	void Resume();
	void Halt();

	void Destroy();

public:
	int 		id   { 0      };
	std::string path { "None" };

	static const std::string DEFAULT_MUSIC;
	static int 	             created_musics;

private:
	Mix_Music*  m_music = nullptr;
};
}