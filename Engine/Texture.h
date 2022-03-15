#pragma once
#define TEXTURE_H
#define SIZE_MATCH_WINDOW true

#include "Window.h"
#include <cstring>

namespace Engine {

SDL_Surface* Load_Surface(Engine::Window* window, const char* path);
SDL_Texture* Load_Texture_Static(Engine::Window* window, const char* path);
SDL_Texture* Load_Texture_Mutable(Engine::Window* window, const char* path, void* pixels, int& pitch, ISize& img_size);

SDL_Surface* Load_Surface(Engine::Window* window, String path);
SDL_Texture* Load_Texture_Static(Engine::Window* window, String path);


void Render_Case_Negative_Size(IRect&    rect);
void Render_Case_Negative_Size(FRect&    rect);
void Render_Case_Negative_Size(SDL_Rect& rect);


// -ID takes up all positive numbers int can hold. 
// -Use negative for custom.
class Texture 
{
public:
	Texture(Engine::Window* p_window, const char* p_path);
	Texture(Engine::Window* p_window, String p_path);
	Texture();
	~Texture();

	void New_ID();

	// Getters
	const  SDL_Texture* operator()() const;
		   SDL_Texture* Get_SDL_Texture() const;	
	Texture Get_Default();

	// Loaders
	bool         Load(Engine::Window* p_window,  SDL_Texture* p_texture);
	bool         Load(Engine::Window* p_window,  String p_path);
	virtual bool Load(Engine::Window* p_window,  const char* p_path);

	virtual bool Load_Mutable(Engine::Window* p_window, String p_path);

	// Renders
	void Render(IRect  p_rect, const SDL_Rect* p_clip = NULL) const;
	void Render(FRect  p_rect, const SDL_Rect* p_clip = NULL) const;
	void Render(const SDL_Rect* p_rect, const SDL_Rect* p_clip = NULL) const;

	bool Lock();
	bool Unlock();

	// Color manipulaations.
	void Set_Opacity(Uint8   p_alpha);
	// Modulating grayscale result to original color. 
	void Set_Color(Color     p_color);
	void Set_Color(SDL_Color p_color);

	void Set_Color(Uint8 p_red, Uint8 p_green, Uint8 p_blue);

	// After-effects.
	virtual void Destroy();

public:
	// Informations //
	int 			  id    { 0      };
	float 			  angle { 360.0  };
	SDL_Point*        center{ nullptr };
	SDL_RendererFlip  flip  { SDL_FLIP_NONE };
	String      	  path  { "None" };

	// Attributes //
	void* pixels { nullptr };
	int   pitch  { 0       };
	ISize size   { 0, 0    };

protected:
	Engine::Window*  m_window  { nullptr };
	SDL_Texture*     m_texture { nullptr };

private:
	static Texture  s_default_texture;
	bool 		    m_pointing { false }; 	// No heap allocation made. Will not destroy.
}; 


};
