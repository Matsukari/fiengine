#pragma once
#define COLOR_H

#include <SDL.h>
#include <iostream>
#include <cstdint>

struct Color
{
	// Credits to javidx9.
	static const Color 
		GREY, 		DARK_GREY, 		VERY_DARK_GREY,
		RED, 		DARK_RED, 	 	VERY_DARK_RED,
		YELLOW, 	DARK_YELLOW, 	VERY_DARK_YELLOW,
		GREEN,		DARK_GREEN,	 	VERY_DARK_GREEN,
		CYAN,		DARK_CYAN,	 	VERY_DARK_CYAN,
		BLUE,		DARK_BLUE,	 	VERY_DARK_BLUE,
		MAGENTA,	DARK_MAGENTA,	VERY_DARK_MAGENTA,
		BROWN, 		WHITE,			BLACK;

	Uint8 	r;  
	Uint8 	g;  
	Uint8 	b;
	// Intermediary varibale for SDL type. Static to interact with const.
	static SDL_Color  sdl_color;

	SDL_Color operator()() const;
	SDL_Color Get_SDL_Color() const;

	Color Get_Negative() const;
	Color To_Negative();

	Color Set_Brightness(uint8_t p_brightness);
	Color Set_Darkness(  uint8_t p_darkness);
};