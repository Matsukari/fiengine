#include "Sound.h"

namespace Engine
{
	const std::string Sound::DEFAULT_SOUND  = "Assets/Sounds/Nulled_Sound.ogg";
	int 	          Sound::created_sounds = 0;

	Sound::Sound(const char* p_path)
	{
		Load(p_path);

		// create id.
		created_sounds++;
		id = created_sounds;
	}
	Sound::Sound()
	{
		// create id.
		created_sounds++;
		id = created_sounds;
	}
	Sound::~Sound()
	{
		Destroy();
	}

	bool Sound::Load(const char* p_path)
	{
		Destroy();
		path = p_path;

		if (m_sound == NULL)
		{
			m_sound = Mix_LoadWAV(p_path);

			// Use default cound.
			if (m_sound == NULL)
			{
				printf("\nError: %s", Mix_GetError());

				m_sound = Mix_LoadWAV(DEFAULT_SOUND.c_str());
				if (m_sound == NULL)
				{
					printf("\nCannot Finc Defauts. Asset Folder Corrupted!");
				}
				return false;
			}
		}
		return true;
	}
	bool Sound::Load(std::string p_path)
	{
		return (Load(p_path.c_str()));
	}

	void Sound::Play(int channel, int p_loops)
	{
		Mix_PlayChannel(channel, m_sound, p_loops);
	}
	void Sound::Play_Timed(int p_ticks, int p_loops)
	{
		Mix_PlayChannelTimed(-1, m_sound, p_loops, p_ticks);
	}
	void Sound::Set_Volume(int p_volume)
	{
		Mix_VolumeChunk(m_sound, p_volume);
	}

	void Sound::Destroy()
	{
		if (m_sound != NULL) 
		{
			printf("\nDestroyed Sound %s", path.c_str());

			Mix_FreeChunk(m_sound);
			m_sound = nullptr;
		}
	}


	const std::string Music::DEFAULT_MUSIC  = "Assets/Sounds/Nulled_Sound.ogg";
	int 	          Music::created_musics = 0;

	Music::Music(const char* p_path)
	{
		Load(p_path);

		// create id.
		created_musics++;
		id = created_musics;
	}
	Music::Music()
	{
		// create id.
		created_musics++;
		id = created_musics;
	}
	Music::~Music()
	{
		Destroy();
	}

	bool Music::Load(const char* p_path)
	{
		Destroy();
		path = p_path;

		if (m_music == NULL)
		{
			m_music = Mix_LoadMUS(p_path);

			// Use default cound.
			if (m_music == NULL)
			{
				printf("\nError: %s", Mix_GetError());

				m_music = Mix_LoadMUS(DEFAULT_MUSIC.c_str());
				if (m_music == NULL)
				{
					printf("\nCannot Find Defaults. Asset Folder Corrupted!");
				}
				return false;
			}
		}
		return true;
	}
	bool Music::Load(std::string p_path)
	{
		return (Load(p_path.c_str()));
	}


	void Music::Play(int p_loops)
	{
		if (not(Mix_PlayingMusic()))
		{
			Mix_PlayMusic(m_music, p_loops);
		}
	}
	void Music::Set_Volume(int p_volume)
	{
		Mix_VolumeMusic(p_volume);
	}
	void Pause()
	{
		if (Mix_PlayingMusic())
		{
			Mix_PauseMusic();
		}
	}
	void Resume()
	{
		if (Mix_PausedMusic())
		{
			Mix_ResumeMusic();
		}
	}
	void Halt()
	{
		Mix_HaltMusic();
	}

	void Music::Destroy()
	{
		if (m_music != NULL) 
		{
			printf("\nDestroyed Sound %s", path.c_str());

			Mix_HaltMusic();
			Mix_FreeMusic(m_music);
			m_music = nullptr;
		}
	}

}