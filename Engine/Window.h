#pragma once
#define WINDOW_H

#include <fstream>
#include "Cpplib.h"

#include "Log.h"
#include "Math.h"
#include "File.h"
#include "Color.h"
#include "Shapes.h"
#include "Graphic_Draw.h"

#include "SDLU.h"

// Most member functions are, the same in SDL, only changed in function name.
// Note: Mix audio is opened at the beginning! Feel free to use Destroy() every time you create new exdata. 
namespace Engine
{
class Window 
{
public:
	Window(String p_title, String p_directory, ISize p_size,  Uint32 p_window_flags, Uint32 p_renderer_flags);
	Window(const char* p_path);
	~Window();

	// almost all sdl window functions are non const/
	const SDL_Window* operator()() const;
	SDL_Window* Get_Window() const;

	void Handle_Events(SDL_Event& p_event);
	void Update();
	void Render_Clear() const;
	void Render(Color p_color, Uint8 p_alpha = SDL_ALPHA_OPAQUE);

	void ReOpen_Audio(int p_frequency, Uint16 p_format, int p_channels, int p_chunksize);
	// Assume SDL_Window is already loaded of created.
	void Convert_Window_From(SDL_Window* p_window, SDL_Renderer* p_renderer, Uint32 p_wflags, Uint32 p_rflags);

	void Set_Icon(const char *p_icon);
	void Set_Background(Color p_color);

	void Destroy();
	void Show_Fps();

private:
	void DEFAULT_INIT_MEMBERS();
	// Uses title, w, h member.
	bool Create_Window(Uint32   p_flags);
	bool Create_Renderer(Uint32 p_flags);

	void Test_Fps();

public:
	// Careful accessing members directly. Mutables.
	Text_File asset_paths;

	// Base Directory..
	String  directory;
	String  assets_dir;
	String  imgs_dir;
	String  fonts_dir;
	String  sounds_dir;

	SDL_Window*   window;
	SDL_Renderer* renderer;

	// Size must be int to query SDL_window for size.
	ISize   size;
	String  title;

	Uint32 window_flags;
	Uint32 renderer_flags;

	bool   has_quit;
	bool   is_running;
	bool   is_resized;

	int   fps;

	// The change in size of the window.
	// Add this in rect size to match window.
	ISize  changed_size;
	ISize  old_size;

	ELog   log;

private:
	Color m_background_color;

	Uint32 m_last_counted_frames;
	int    m_counted_frames;

};

/*
___________________________________________________________________________________________________________________________________
	SDL_Window Functions
___________________________________________________________________________________________________________________________________

SDL_CreateWindow()
SDL_CreateWindowFrom()
SDL_DestroyWindow()
SDL_GetWindowData()
SDL_GetWindowFlags()
SDL_GetWindowGrab()
SDL_GetWindowPosition()
SDL_GetWindowSize()
SDL_GetWindowTitle()
SDL_HideWindow()
SDL_MaximizeWindow()
SDL_MinimizeWindow()
SDL_RaiseWindow()
SDL_RestoreWindow()
SDL_SetWindowData()
SDL_SetWindowFullscreen()
SDL_SetWindowGrab()
SDL_SetWindowIcon()
SDL_SetWindowPosition()
SDL_SetWindowSize()
SDL_SetWindowBordered()
SDL_SetWindowResizable()
SDL_SetWindowTitle()
SDL_ShowWindow()
___________________________________________________________________________________________________________________________________
*/




/*
SDL_SetClipboardText(const char*) - void
SDL_GetClipboardText() - char*

SDL_GetModState() & KMOD_CTRL

*/

} // namespace

