#pragma once
#define GRAPHIC_DRAW_H

#include "Math.h"
#include "Color.h"
#include "Shapes.h"

struct ILine
{
	int x1; int y1;
	int x2; int y2;
};
struct FLine
{
	float x1; float y1;
	float x2; float y2;
};
struct Graphic_IRect
{
	Color  color;
	IRect  rect;

	Uint8   alpha = SDL_ALPHA_OPAQUE;
};
struct Graphic_FRect
{
	Color  color;
	FRect  rect;

	Uint8   alpha = SDL_ALPHA_OPAQUE;
};
struct Graphic_ILine
{
	Color  color;
	ILine  line;

	Uint8   alpha = SDL_ALPHA_OPAQUE;

};
struct Graphic_FLine
{
	Color  color;
	FLine  line;

	Uint8   alpha = SDL_ALPHA_OPAQUE;

};
struct Graphic_IPoint
{
	Color color;
	IAxis point;

	Uint8  alpha = SDL_ALPHA_OPAQUE;
};
struct Graphic_FPoint
{
	Color color;
	FAxis point;

	Uint8  alpha = SDL_ALPHA_OPAQUE;
};

namespace Engine {

void Draw_Rect_Fill   (SDL_Renderer* renderer, const Graphic_IRect& graph);
void Draw_Rect_Fill   (SDL_Renderer* renderer, const Graphic_FRect& graph);

void Draw_Rect_Outline(SDL_Renderer* renderer, const Graphic_IRect& graph);
void Draw_Rect_Outline(SDL_Renderer* renderer, const Graphic_FRect& graph);

void Draw_Line        (SDL_Renderer* renderer, const Graphic_ILine& graph);
void Draw_Line        (SDL_Renderer* renderer, const Graphic_FLine& graph);

void Draw_Pixel_Dot   (SDL_Renderer* renderer, const Graphic_IPoint& dot);
void Draw_Pixel_Dot   (SDL_Renderer* renderer, const Graphic_FPoint& dot);
}