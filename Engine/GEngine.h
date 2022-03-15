#pragma once

// No support classes for TTF_Font
#ifndef ENGINE_H
	#define ENGINE_H

	#include <iostream>
	#include <cstdlib>
	#include <vector>
	#include <string>
	#include <sys/time.h>
	#include <time.h>
	#include <ctime>

	#include "SDLU.h"
	
	#include "Math.h"
	#include "Color.h"
	#include "Shapes.h"
	#include "Graphic_Draw.h"

	#include "Searcher.h"

	#include "Spritesheet.h"
	#include "Log.h"
	#include "Window.h"
	#include "Texture.h"
	#include "Bitmap_Font.h"
	#include "Sound.h"

	#include "Collision.h"
	#include "File.h"

	#include "Events.h"

	void Engine_Reset();
	void Engine_End();

	
#endif