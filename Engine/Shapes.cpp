#include "Shapes.h"


/*__Rect class Implements___________________________________________________________________________________________________*/
SDL_Rect IRect::rect = {0, 0, 0, 0};
SDL_FRect IRect::frect = {0.0, 0.0, 0.0, 0.0};


const SDL_Rect* IRect::operator()() const
{
	return &(IRect::rect = {x, y, w, h});
}
SDL_Rect* IRect::Get_SDL_Rect() const
{
	return &(IRect::rect = {x, y, w, h});
}
SDL_FRect* IRect::Get_SDL_FRect() const
{
	return &(IRect::frect = {static_cast<float>(x), static_cast<float>(y), 
						     static_cast<float>(w), static_cast<float>(h)} );
}


int IRect::Top()    const  { return y;     }
int IRect::Bottom() const  { return y + h; }
int IRect::Left()   const  { return x;     }
int IRect::Right()  const  { return x + w; }

// Move the center of (*this rect) to the (center of provided rect).
IRect IRect::Center(IRect _rect) 
{ 
	return IRect
	{
		.x = static_cast<int>(_rect.Center_X() - (w/2)),  
		.y = static_cast<int>(_rect.Center_Y() - (h/2)), 
		.w = w, 
		.h = h
	};
}

float IRect::Center_X() const 
{ 
	return static_cast<float>(x + (w / 2)); 
}
float IRect::Center_Y() const 
{
	return static_cast<float>(y + (h / 2)); 
}


/*FRect class Implemetrs___________________________________________________________________________________________________*/
SDL_FRect FRect::frect = {0.0, 0.0, 0.0, 0.0};
SDL_Rect  FRect::rect = {0, 0, 0, 0};


const SDL_FRect* FRect::operator()() const 
{ 
	return &(FRect::frect = {x, y, w, h}); 
}
SDL_FRect* FRect::Get_SDL_FRect() const 
{ 
	return &(FRect::frect = {x, y, w, h}); 
}
SDL_Rect* FRect::Get_SDL_Rect() const 
{ 
	return &(FRect::rect = {static_cast<int>(x), static_cast<int>(y), 
			                 static_cast<int>(w), static_cast<int>(h)} ); 
}


float FRect::Top()    const  { return y;     }
float FRect::Bottom() const  { return y + h; }
float FRect::Left()   const  { return x;     }
float FRect::Right()  const  { return x + w; }

// Move the center of (*this rect) to the (center of provided rect).
FRect FRect::Center(FRect _rect) 
{ 
	return FRect
	{
		.x = _rect.Center_X() - (w/2),  
		.y = _rect.Center_Y() - (h/2), 
		.w = w, 
		.h = h
	};  
}

float FRect::Center_X() const 
{ 
	return static_cast<float>(x + (w / 2)); 
}
float FRect::Center_Y() const 
{
	return static_cast<float>(y + (h / 2));
}

// IRect operator ==
void IRect::operator=(const FRect& p_rect)
{
	x = static_cast<int>(p_rect.x);
	y = static_cast<int>(p_rect.y);
	w = static_cast<int>(p_rect.w);
	h = static_cast<int>(p_rect.h);
}
void IRect::operator=(const SDL_Rect& p_rect)
{
	x = p_rect.x;
	y = p_rect.y;
	w = p_rect.w;
	h = p_rect.h;
}

// FRect operator ==
void FRect::operator=(const IRect& p_rect)
{
	x = static_cast<float>(p_rect.x);
	y = static_cast<float>(p_rect.y);
	w = static_cast<float>(p_rect.w);
	h = static_cast<float>(p_rect.h);
}
void FRect::operator=(const SDL_Rect& p_rect)
{
	x = static_cast<float>(p_rect.x);
	y = static_cast<float>(p_rect.y);
	w = static_cast<float>(p_rect.w);
	h = static_cast<float>(p_rect.h);
}
