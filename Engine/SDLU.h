#pragma once
#define SDLU_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <sys/time.h>
#include <time.h>

#include "Cpplib.h"
#include "Math.h"
#include "Log.h"

int  SDLU_Random(IRange range);

bool SDLU_Check_Error(bool condition = true);
bool MixU_Check_Error(bool condition = true);
bool TTFU_Check_Error(bool condition = true);
bool IMGU_Check_Error(bool condition = true);

// Call this before anything else.
bool Start_SDL(Uint32 init_flags = SDL_INIT_EVERYTHING);
void End_SDL();
