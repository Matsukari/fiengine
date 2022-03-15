#include "Graphic_Draw.h"

namespace Engine {


void Draw_Rect_Fill(SDL_Renderer* renderer, const Graphic_IRect& graph) 
{
	SDL_SetRenderDrawColor(renderer, graph.color.r, graph.color.g, graph.color.b, graph.alpha);

	SDL_RenderFillRect(renderer, graph.rect());
}
void Draw_Rect_Fill(SDL_Renderer* renderer, const Graphic_FRect& graph) 
{
	SDL_SetRenderDrawColor(renderer, graph.color.r, graph.color.g, graph.color.b, graph.alpha);

	SDL_RenderFillRectF(renderer, graph.rect());
}


void Draw_Rect_Outline(SDL_Renderer* renderer, const Graphic_IRect& graph) 
{
	SDL_SetRenderDrawColor(renderer, graph.color.r, graph.color.g, graph.color.b, graph.alpha);

	SDL_RenderDrawRect(renderer, graph.rect());
}
void Draw_Rect_Outline(SDL_Renderer* renderer, const Graphic_FRect& graph) 
{
	SDL_SetRenderDrawColor(renderer, graph.color.r, graph.color.g, graph.color.b, graph.alpha);

	SDL_RenderDrawRectF(renderer, graph.rect());
}



void Draw_Line(SDL_Renderer* renderer, const Graphic_ILine& graph) 
{
	SDL_SetRenderDrawColor(renderer, graph.color.r, graph.color.g, graph.color.b, graph.alpha);

	SDL_RenderDrawLine(renderer, graph.line.x1, graph.line.y1, 
								 graph.line.x2, graph.line.y2);
}
void Draw_Line(SDL_Renderer* renderer, const Graphic_FLine& graph) 
{
	SDL_SetRenderDrawColor(renderer, graph.color.r, graph.color.g, graph.color.b, graph.alpha);

	SDL_RenderDrawLineF(renderer, graph.line.x1, graph.line.y1, 
								 graph.line.x2, graph.line.y2);
}

void Draw_Pixel_Dot(SDL_Renderer* renderer, const Graphic_IPoint& graph) 
{
	SDL_SetRenderDrawColor(renderer, graph.color.r, graph.color.g, graph.color.b, graph.alpha);

	SDL_RenderDrawPoint(renderer, graph.point.x, graph.point.y);
}
void Draw_Pixel_Dot(SDL_Renderer* renderer, const Graphic_FPoint& graph) 
{
	SDL_SetRenderDrawColor(renderer, graph.color.r, graph.color.g, graph.color.b, graph.alpha);

	SDL_RenderDrawPointF(renderer, graph.point.x, graph.point.y);
}


} // namespace