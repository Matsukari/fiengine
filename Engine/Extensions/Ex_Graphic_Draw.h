#pragma once
#define EX_GRAPHIC_DRAW_H

#include "../Math.h"
#include "../Window.h"
#include "../Bitmap_Font.h"

namespace Engine 
{
void Draw_Grid_Line(SDL_Renderer* renderer, Color color, IAxis start, IAxis end, IAxis margin);
void Draw_Fps(Engine::Window* window, const Engine::Bitmap_Font* font);
}