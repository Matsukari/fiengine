#pragma once
#define FONT_H
#define ENGINE_LOCAL_FONT_P58  "Assets/Fonts/square_pixel_58.png" // SPECIFY the root dir first!!!!!!! 
#define ENGINE_LOCAL_ALPHABET  "Assets/Fonts/square_pixel_58.alphabet"
#define ENGINE_ASCII_ALPHABET  "Null"

#include <map>
#include <iterator>

#include "Window.h"
#include "Texture.h"

enum ALIGNMENT 
{ 
	ALIGN_LEFT, 
	ALIGN_RIGHT, 
	ALIGN_CENTER 
};
// Can't pass by value; Crashes, so pass it as pointer.
struct Graphic_IText
{
	Vector<String> content;
	Color   	   color;
	IRect		   rect;

	// In window pixels. Only addition. Bitmap_Font Render is ordered.
	int 	 space_margin   = 0;
	int      newline_margin = 0;

	uint8_t  alpha          = SDL_ALPHA_OPAQUE;
};
struct Graphic_FText
{
	Vector<String> content;
	Color   	   color;
	FRect		   rect;

	// In window pixels. Only addition. Bitmap_Font Render is ordered.
	int 	 space_margin   = 0;
	int      newline_margin = 0;

	uint8_t  alpha          = SDL_ALPHA_OPAQUE;
};
// Do not initialize. This is will be loaded in Bitmap_Font::Preload_Text().
struct Text_IPosition
{
	Vector<IRect>    render_pos = {}; // The position of each letters to render.
	Vector<SDL_Rect> letter_pos = {}; // Letters rect from Bitmap_Font to clip for spritesheet.
};
struct Text_FPosition
{
	Vector<FRect>    render_pos = {};
	Vector<SDL_Rect> letter_pos = {};
};

namespace Engine {

class Bitmap_Font 
{
public:
	Bitmap_Font(Engine::Window* p_window, const char* p_path, Vector<String> p_placement, ISize p_cut_size);
	Bitmap_Font(Engine::Window* p_window, const char* p_path, const char* p_file_path);
	Bitmap_Font(Engine::Window* p_window, const char* p_path, const char* p_file_path, const Graphic_IText& p_text, Text_IPosition& p_pos);
	Bitmap_Font();
	~Bitmap_Font();

	const Engine::Texture* operator()()  const { return m_texture; }
		  Engine::Texture* Get_Texture() const { return m_texture; }


	void Load(Engine::Window* p_window, const char* p_path);
	void Load(Engine::Window* p_window, String p_path);
	void Configure_Placement(Vector<String> p_placement, ISize p_cut_size);
	void Configure_Placement(const char* p_file_path);

	// Do well for constant rendering.
	// Sets Graphic_Text's corresponding position for rendering.
	void Preload_Text(const Graphic_IText& p_text, Text_IPosition& p_pos);
	void Preload_Text(const Graphic_FText& p_text, Text_FPosition& p_pos);
	// Counter parts of ABOVE-
	void Preload_Text(const Graphic_IText& p_text, Text_FPosition& p_pos);
	void Preload_Text(const Graphic_FText& p_text, Text_IPosition& p_pos);


	void Render_Prepared(const Text_IPosition& p_pos) const;
	void Render_Prepared(const Text_FPosition& p_pos) const;

	// Set's the texture color and alpha from Graphic_Text.
	void Render(const Graphic_IText& p_text) const; 
	void Render(const Graphic_FText& p_text) const;

	 // Ignore color and alpha from Graphic_text.
	void Render(const Graphic_IText& p_text);
	void Render(const Graphic_FText& p_text);

	void Destroy();

	int id;

private:
	Engine::Window*  m_window;
	Engine::Texture* m_texture;
	std::map<char, SDL_Rect> m_alphabet;

	ISize m_cut_size;
	bool  m_is_loaded {false};

	// Used to make Render method, const. std::map::find() apparently not const'd.
	// Points to m_alphabet.
	static std::map<char, SDL_Rect>* s_share_alphabet;
};

}