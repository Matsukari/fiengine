#include "SDLU.h"

int SDLU_Random(IRange range)
{
	timeval t;

	SDL_Delay(1);

	gettimeofday(&t, NULL);
	srand(t.tv_usec * t.tv_sec);
	
	// if minimum is negative then possible results reduces from that minimum to half maximum,
	// make up by adding extra half to make if whole.
	if (range.min < 0) {range.max *= 2;}

	return (rand() % range.max) + range.min;
}


bool SDLU_Check_Error(bool condition)
{
	if (condition == true)
	{
		ELog_Runtime(SDL_GetError(), LOG_ERROR);
		return true;
	}
	return false;
}
bool MixU_Check_Error(bool condition)
{
	if (condition == true)
	{
		ELog_Runtime(Mix_GetError(), LOG_ERROR);
		return true;
	}
	return false;
}
bool TTFU_Check_Error(bool condition)
{
	if (condition == true)
	{
		ELog_Runtime(TTF_GetError(), LOG_ERROR);
		return true;
	}
	return false;
}
bool IMGU_Check_Error(bool condition)
{
	if (condition == true)
	{
		ELog_Runtime(IMG_GetError(), LOG_ERROR);
		return true;
	}
	return false;
}




bool Start_SDL(Uint32 init_flags)
{
	static bool FAILED_BEFORE = true;

	bool success   = true;
	int  img_flags = IMG_INIT_PNG | IMG_INIT_JPG;

	// Only once and if failed befoer
	if (FAILED_BEFORE)
	{
		if (SDL_Init(init_flags) == -1) 
		{
			SDLU_Check_Error();
			success = false;
		}
		else
		{
			// Procceds if sdl initializes properly.
			if (!IMG_Init(img_flags) & img_flags) 
			{
				IMGU_Check_Error();
				success = false;
			}

			if (TTF_Init() == -1) 
			{
				TTFU_Check_Error();
				success = false;
			}
			// Frequency: 22050(MIX_DEFAULT_FREQUENCY), 44100 - cd audio rate
			// Sound channel: 2 - stereo, 1 - mono
			// Activated right from the beginning.
			if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) < 0) 
			{
				MixU_Check_Error();
				success = false;
			}
		}
		if (success)
		{
			FAILED_BEFORE = false;
			ELog_Runtime("Successfully initialized SDL and its extensions.", LOG_MSG);
		}
		else
			ELog_Runtime("SDL initialized but one or more SDL extensions failed to.", LOG_ERROR);
	}


	return success;
}
void End_SDL()
{
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();

	ELog_Runtime("SDL Ended.", LOG_MSG);
}