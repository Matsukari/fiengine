#pragma once
#define SPRITESHEET_H
#define DIRECTION_FRONT 0 // Not a direction at all.

#include <SDL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "Math.h"
#include "Log.h"

enum EXTRACT_ORDER
{
	ORDER_LEFT_TO_RIGHT,
	ORDER_TOP_TO_BOTTOM
};

struct Sprite_Extract_Info
{
	IAxis          start;
	ISize           sheet;
	ISize           cut;
	EXTRACT_ORDER  order;
};

// For 1 side. vector - the storage dump for all extracted rects. 
void Extract_Spritesheet(Vector<SDL_Rect>& vector, Sprite_Extract_Info sprite, short frames);
void Extract_Spritesheet(Vector<SDL_Rect>& vector, const char* sprite_path);

/*FILE ORDER
Start_Pos: _ _
Sheet_Size: _ _
Cut_Size: _ _
Order: _(only and exactly only "left_to_right" "top_to_bottom")

Frames: _
*/