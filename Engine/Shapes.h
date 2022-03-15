#pragma once
#define SHAPES_H

#include <SDL.h>
#include <fstream>

#include "Cpplib.h"

struct IRect; // forward declaration. To know class name for FRect operator=(assignment).

struct FRect
{
	float x;  float y;
	float w;  float h;
	static SDL_FRect frect;
	static SDL_Rect  rect;

	const SDL_FRect* operator()() const;
		  SDL_FRect* Get_SDL_FRect() const;
		  SDL_Rect*  Get_SDL_Rect() const;

	explicit operator const SDL_FRect*() const { return &(FRect::frect = {x, y, w, h}); }
	explicit operator const SDL_Rect*()  const { return &(FRect::rect  = {static_cast<int>(x), static_cast<int>(y), 
																		   static_cast<int>(w), static_cast<int>(h)} ); }
	// Still dont know about IRect. Implement after defining IRect.
	void operator=(const IRect& p_rect);
	void operator=(const SDL_Rect& p_rect);

	float Top()    const;
	float Bottom() const;
	float Left()   const;
	float Right()  const;

	// Move the center of (*this rect) to the (center of provided rect).
	FRect Center(FRect _rect);

	float Center_X() const;
	float Center_Y() const;

	friend std::ofstream& operator<<(std::ofstream& ofile, const FRect& p_rect)
	{
		ofile << "x: " << p_rect.x;
		ofile << "y: " << p_rect.y;
		ofile << "w: " << p_rect.w;
		ofile << "h: " << p_rect.h;

		return ofile;
	}
	friend std::ifstream& operator>>(std::ifstream& ifile, FRect& p_rect)
	{
		std::string name;
		ifile >> name >> p_rect.x;
		ifile >> name >> p_rect.y;
		ifile >> name >> p_rect.w;
		ifile >> name >> p_rect.h;

		return ifile;
	}
}; 


struct IRect
{
	int x;  int y;
	int w;  int h;
	// Serves as referenced variable for sdl intermideary
	static SDL_Rect rect;
	static SDL_FRect frect;

	const SDL_Rect* operator()() const;
		  SDL_Rect*  Get_SDL_Rect() const;
		  SDL_FRect* Get_SDL_FRect() const;

	explicit operator const SDL_Rect*() const { return &(IRect::rect  = {x, y, w, h}); }
	explicit operator const SDL_FRect*() const { return &(IRect::frect = {static_cast<float>(x), static_cast<float>(y), 
																	      static_cast<float>(w), static_cast<float>(h)} ); }
	// Knows about FRect; Already defined exluding operator==.
	void operator=(const FRect& p_rect);
	void operator=(const SDL_Rect& p_rect);

	int Top()    const;
	int Bottom() const;
	int Left() 	 const;
	int Right()  const;

	// Move the center of (*this rect) to the (center of provided rect).
	// By Value.
	IRect Center(IRect _rect);

	float Center_X() const;
	float Center_Y() const;

	friend std::ofstream& operator<<(std::ofstream& ofile, const IRect& p_rect)
	{
		ofile << "x: " << p_rect.x << " ";
		ofile << "y: " << p_rect.y << " ";
		ofile << "w: " << p_rect.w << " ";
		ofile << "h: " << p_rect.h << " ";

		return ofile;
	}
	friend std::ifstream& operator>>(std::ifstream& ifile, IRect& p_rect)
	{
		std::string name;
		ifile >> name >> p_rect.x;
		ifile >> name >> p_rect.y;
		ifile >> name >> p_rect.w;
		ifile >> name >> p_rect.h;
		
		return ifile;
	}
}; 

struct ICircle
{
	// center x, y
	int x;  int y;
	int r;

	int TopLeft_X() const { return x - r; }
	int TopLeft_Y() const { return y - r; }

	int Diameter() const { return (r + r ); }

	friend std::ofstream& operator<<(std::ofstream& ofile, const ICircle& p_circle)
	{
		ofile << "x: " << p_circle.x;
		ofile << "y: " << p_circle.y;
		ofile << "r: " << p_circle.r;

		return ofile;
	}
	friend std::ifstream& operator>>(std::ifstream& ifile, ICircle& p_circle)
	{
		std::string name;
		ifile >> name >> p_circle.x;
		ifile >> name >> p_circle.y;
		ifile >> name >> p_circle.r;

		return ifile;
	}
};

struct FCircle
{
	// center x, y
	float x;  float y;
	float r;

	float TopLeft_X() const { return x - r; }
	float TopLeft_Y() const { return y - r; }

	float Diameter() const { return (r + r ); }

	friend std::ofstream& operator<<(std::ofstream& ofile, const FCircle& p_circle)
	{
		ofile << "x: " << p_circle.x;
		ofile << "y: " << p_circle.y;
		ofile << "r: " << p_circle.r;

		return ofile;
	}
	friend std::ifstream& operator>>(std::ifstream& ifile, FCircle& p_circle)
	{
		std::string name;
		ifile >> name >> p_circle.x;
		ifile >> name >> p_circle.y;
		ifile >> name >> p_circle.r;

		return ifile;
	}
};