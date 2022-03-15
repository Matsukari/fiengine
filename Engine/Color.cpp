#include "Color.h"


SDL_Color Color::sdl_color = {0, 0, 0};

SDL_Color Color::Get_SDL_Color() const
{ 
	return sdl_color = {r, g, b}; 
}
Color Color::Get_Negative() const
{  
	return Color
	{
		static_cast<Uint8>(255 - r), 
		static_cast<Uint8>(255 - g), 
		static_cast<Uint8>(255 - b)
	}; 
}
Color Color::To_Negative() 
{ 
	return (*this = Get_Negative());  
}

Color Color::Set_Brightness(uint8_t p_brightness)
{
	r += p_brightness;
	g += p_brightness;
	b += p_brightness;

	return *this;
}
Color Color::Set_Darkness(uint8_t p_darkness)
{
	r -= p_darkness;
	g -= p_darkness;
	b -= p_darkness;
	
	return *this;
}
const Color 
	Color::GREY 	= {192, 192, 192},      Color::DARK_GREY 	 = {128, 128, 128},    Color::VERY_DARK_GREY 	 = {64, 64, 64},
	Color::RED 		= {255,   0,   0},      Color::DARK_RED 	 = {128,   0,   0},    Color::VERY_DARK_RED	     = {64,  0,  0},
	Color::YELLOW  	= {255, 255,   0},      Color::DARK_YELLOW   = {128, 128,   0},    Color::VERY_DARK_YELLOW   = {64, 64,  0},
	Color::GREEN 	= {  0, 255,   0},      Color::DARK_GREEN    = {  0, 128,   0},	   Color::VERY_DARK_GREEN    = { 0, 64,  0},
	Color::CYAN 	= {  0, 255, 255},      Color::DARK_CYAN 	 = {  0, 128, 128},	   Color::VERY_DARK_CYAN 	 = { 0, 64, 64},
	Color::BLUE 	= {  0,   0, 255},      Color::DARK_BLUE 	 = {  0,   0, 128},	   Color::VERY_DARK_BLUE 	 = { 0,  0, 64},
	Color::MAGENTA 	= {255,   0, 255},      Color::DARK_MAGENTA  = {128,   0, 128},	   Color::VERY_DARK_MAGENTA  = {64,  0, 64},
	Color::BROWN 	= {205, 133,  63},      Color::WHITE 		 = {255, 255, 255},	   Color::BLACK 			 = { 0,  0,  0};