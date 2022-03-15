#include "Ex_Graphic_Draw.h"


namespace Engine
{

void Draw_Grid_Line(SDL_Renderer* renderer, Color color, IAxis start, IAxis end, IAxis margin)
{
	Graphic_ILine graph = {
		.color    = color,
		.line     = {0, 0, 0, 0}
	};

	// Vertical Lines.
	for (unsigned short i = start.x; i <= end.x; i += margin.x) 
	{
		graph.line.x1 = i;
		graph.line.x2 = i;

		graph.line.y1 = 0;
		graph.line.y2 = end.y;

		Draw_Line(renderer, graph);
	}

	// Horizontal Lines.
	for (unsigned short i = start.y; i <= end.y; i += margin.y) 
	{
		graph.line.x1 = 0; 
		graph.line.x2 = end.x;

		graph.line.y1 = i;
		graph.line.y2 = i;

		Draw_Line(renderer, graph);
	}
}

void Draw_Fps(Engine::Window* window, const Engine::Bitmap_Font* font)
{
	static Graphic_IText text = 
	{
		.content        = {std::to_string(0)},
		.color          = Color::WHITE,
		.rect           = {5, 5, 30, 30},
	};
	text.content[0] = std::to_string(window->fps);
	font->Render(text);
}

}