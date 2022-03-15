#include "Window.h"


namespace Engine
{

Window::Window(String p_title, String p_directory, ISize p_size, Uint32 p_window_flags, Uint32 p_renderer_flags) : asset_paths()
{
	DEFAULT_INIT_MEMBERS();

	directory = p_directory;

	size.w = p_size.w;
	size.h = p_size.h;
	title  = p_title;

	window_flags   = p_window_flags;
	renderer_flags = p_renderer_flags;

	old_size.w = size.w;
	old_size.h = size.h;

	// Will only Initialize if sdl failed in previous one or in first time.
	if (Start_SDL())
	{
		Create_Window(p_window_flags);
		Create_Renderer(p_renderer_flags);

		is_running 	= true;
	}
	else 
	{
		is_running = false;
	}
	// Alpha Blending Mode.
	if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) == -1)
	{
		SDLU_Check_Error();
	}

	// Open File, Locations of assets 
	asset_paths.Open(directory + "Locations.atlas");
	assets_dir = directory + asset_paths.Read_After("ASSETS_DIRECTORY:");
	imgs_dir   = directory + asset_paths.Read_After("IMGS_DIRECTORY:");
	fonts_dir  = directory + asset_paths.Read_After("FONTS_DIRECTORY:");
	sounds_dir = directory + asset_paths.Read_After("SOUNDS_DIRECTORY:");


	log("Called Constructor of Window", LOG_MSG);
	(is_running) ?	log("Window Running", LOG_MSG) : log("Window Failed to Run!", LOG_ERROR);
}
Window::Window(const char* p_path)
{
	DEFAULT_INIT_MEMBERS();

	log("Called Window constructor alternative(From File)", LOG_MSG);
}

Window::~Window() 
{
	Destroy();
	log("Called Destructor of Window", LOG_MSG);

	std::ofstream file("Logs.txt", std::ios::out | std::ios::trunc);
	file << log;
	file.close();
}
const SDL_Window* Window::operator()() const
{
	return window;
}
SDL_Window* Window::Get_Window() const
{
	return window;
}

void Window::Handle_Events(SDL_Event& p_event)
{
	if(p_event.type == SDL_QUIT ||
	  (p_event.type == SDL_WINDOWEVENT && p_event.window.event   == SDL_WINDOWEVENT_CLOSE) ||
	  (p_event.type == SDL_KEYDOWN     && p_event.key.keysym.sym == SDLK_ESCAPE))
	{
		is_running = false;
		has_quit   = true;
		
		log("Quitted from Window.", LOG_MSG);
	}
	// Only gets detected after mouse button up.
	if (p_event.type == SDL_WINDOWEVENT && p_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		SDL_GetWindowSize(window, &size.w, &size.h);
		// Before updating old window. Get it old data first.
		changed_size.w = size.w - old_size.w;
		changed_size.h = size.h - old_size.h;

		is_resized = true;

		old_size = size;

		SDL_RenderPresent(renderer);
	}
}
void Window::Update()
{
	SDL_RenderPresent(renderer);
	Test_Fps();
}
void Window::Render_Clear() const
{
	SDL_RenderClear(renderer);
}
void Window::Render(Color p_color, Uint8 p_alpha)
{
	SDL_SetRenderDrawColor(renderer, p_color.r, p_color.g, p_color.b, p_alpha);
}


void Window::ReOpen_Audio(int p_frequency, Uint16 p_format, int p_channels, int p_chunksize)
{
	Mix_CloseAudio(); // One Openned at constructor. For Before 

	if (Mix_OpenAudio(p_frequency, p_format, p_channels, p_chunksize) == -1) 
	{
		MixU_Check_Error();
	}
	else
		log("Re Openned Mixer Audio", LOG_MSG);
}
void Window::Convert_Window_From(SDL_Window* p_window, SDL_Renderer* p_renderer, Uint32 p_wflags, Uint32 p_rflags)
{
	Destroy(); // Call this Before below function set window and renderer to null without freeing.
	DEFAULT_INIT_MEMBERS();

	title = SDL_GetWindowTitle(p_window);
	SDL_GetWindowSize(p_window, &size.w, &size.h);

	old_size.w = size.w;
	old_size.h = size.h;

	window_flags   = p_wflags;
	renderer_flags = p_rflags;

	window   = std::move(p_window);
	renderer = std::move(p_renderer);


	log("Converted SDL window to Engine::Window.", LOG_MSG);
	(is_running) ?	log("Window Running(from Convert)", LOG_MSG) : log("Window Failed to Run!(from convert)", LOG_ERROR);
}


void Window::Set_Icon(const char* p_icon)
{
	SDL_Surface *surface = IMG_Load(p_icon);

	if (surface != NULL)
	{
		SDL_SetWindowIcon(window, surface);
		log("Created Icon From surface", LOG_MSG);
	}
	else
	{
		log("Loaded Surface is NULL.", LOG_WARN);
	}

	SDL_FreeSurface(surface);
}
void Window::Set_Background(Color p_color)
{
	m_background_color = p_color;
}
void Window::Show_Fps()
{
	printf("\nFps: %i", fps);
}

void Window::Destroy()
{
	if (renderer != NULL && window != NULL)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		renderer = nullptr;
		window   = nullptr;
		log("Destroyed Window and Renderer", LOG_MSG);
	}
	
	Mix_CloseAudio();
	log("Closed Mixer Audio.", LOG_MSG);
}

void Window::DEFAULT_INIT_MEMBERS()
{
	window   = NULL;
	renderer = NULL;

	title  = "Default";
	size.w  =  0;
	size.h  =  0;

	window_flags   = 0;
	renderer_flags = 0;

	changed_size.w = 0;
	changed_size.h = 0;
	old_size.w     = 0;
	old_size.h     = 0;

	has_quit   = false;
	is_running = false;
	is_resized = false;

	fps 	   = 0;

	m_background_color    = Color::BLACK;
	m_last_counted_frames = 0;
	m_counted_frames      = 0;

	log("Called Window Default", LOG_MSG);
}
bool Window::Create_Window(Uint32 p_flags) 
{
	if (window == NULL)
	{
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.w, size.h, p_flags);

		if (window == NULL) 
		{
			SDLU_Check_Error();
			return false;
		}
		return true;
	}

	log("Created SDL_Window.", LOG_MSG);
	return false; // if window is already loaded.
}
bool Window::Create_Renderer(Uint32 p_flags)  
{
	if (window != NULL) 
	{
		renderer = SDL_CreateRenderer(window, -1, p_flags);

		if (renderer == NULL)
		{
			SDLU_Check_Error();
			return false;
		}
		return true;
	}
	else
	{
		log("Create Window First!", LOG_WARN);
		SDLU_Check_Error();
	}

	log("Created SDL_Renderer", LOG_MSG);
	return false; // if window is still not in set.
}

void Window::Test_Fps()
{
	// Count how many time the game looped within a second(1000 ms).
	if (SDL_GetTicks() > m_last_counted_frames + 1000) 
	{
		m_last_counted_frames = SDL_GetTicks();

		fps = m_counted_frames;
		m_counted_frames = 0;
	}

	m_counted_frames++;
}

}

