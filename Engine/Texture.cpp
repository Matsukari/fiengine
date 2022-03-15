#include "Texture.h"

namespace Engine {

SDL_Surface* Load_Surface(Engine::Window* window, const char* path)
{
	SDL_Surface* surface = IMG_Load(path);

	if (surface != NULL)
	{
		window->log("Created Surface from: " + String(path), LOG_MSG);
	}
	else
	{
		IMGU_Check_Error();
	}

	return surface;
}

SDL_Texture* Load_Texture_Static(Engine::Window* window, const char* path) 
{
	SDL_Surface* surface = Load_Surface(window, path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(window->renderer, surface);

	if (texture != NULL)
	{
		window->log("Created a Texture from Surface: " + String(path), LOG_MSG);
	}
	else
		window->log("Failed to Create Texture from surface: " + String(path), LOG_WARN);

	SDL_FreeSurface(surface);
	surface = nullptr;

	return texture;
}
SDL_Texture* Load_Texture_Mutable(Engine::Window* window, const char* path, void* pixels, int& pitch, ISize& img_size)
{
	SDL_Surface* surface = Load_Surface(window, path);
	SDL_Texture* texture = nullptr;

	if (surface != NULL)
	{
		// Convert surface to display format of window
		SDL_Surface* formatted = SDL_ConvertSurfaceFormat(surface, SDL_GetWindowPixelFormat(window->window), 0);

		if (formatted == NULL)
		{
			window->log("Unable to convert loaded surface to display format! SDL Error", LOG_ERROR);
			SDLU_Check_Error();
		}
		else
		{
			//Create black texture
			texture = SDL_CreateTexture(window->renderer, SDL_GetWindowPixelFormat(window->window), SDL_TEXTUREACCESS_STREAMING, formatted->w, formatted->h);
			
			if (texture == NULL)
			{
				window->log("Unable to create blank texture!", LOG_ERROR);
				SDLU_Check_Error();
			}
			else
			{
				//Lock texture for manipulation
                if (SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0)
				{
					window->log("Unable to Lock Texture!", LOG_ERROR);
					SDLU_Check_Error();
				}
				else
				{
					//Copy loaded/formatted surface pixels
	                memcpy(pixels, formatted->pixels, formatted->pitch * formatted->h );

	                //Unlock texture to update
	                SDL_UnlockTexture(texture);
	                pixels = NULL;

	                //Get image dimensions
	                img_size.w = formatted->w;
	                img_size.h = formatted->h;

				} // Locking texture
               
			} // creating blank texture


            SDL_FreeSurface(formatted);
            formatted = nullptr;

        } // creating formatted surface

        SDL_FreeSurface(surface);
        surface = nullptr;
	}


	return texture;
}

SDL_Surface* Load_Surface(Engine::Window* window, String path)
{
	return Load_Surface(window, path.c_str());
}
SDL_Texture* Load_Texture_Static(Engine::Window* window, String path)
{
	return Load_Texture_Static(window, path.c_str());
}

void Render_Case_Negative_Size(IRect& rect)
{
	if (rect.w < 0)
	{
		rect.w = abs(rect.w);
		rect.x -= rect.w;
	}
	if (rect.h < 0)
	{
		rect.h = abs(rect.h);
		rect.y -= rect.h;
	}
}
void Render_Case_Negative_Size(FRect& rect)
{
	if (rect.w < 0)
	{
		rect.w = abs(rect.w);
		rect.x -= rect.w;
	}
	if (rect.h < 0)
	{
		rect.h = abs(rect.h);
		rect.y -= rect.h;
	}
}
void Render_Case_Negative_Size(SDL_Rect& rect)
{
	if (rect.w < 0)
	{
		rect.w = abs(rect.w);
		rect.x -= rect.w;
	}
	if (rect.h < 0)
	{
		rect.h = abs(rect.h);
		rect.y -= rect.h;
	}
}


//Statc
Texture Texture::s_default_texture;


// Texture functions _______________________________________________________________________________________________________________
Texture::Texture(Engine::Window* p_window, const char* p_path) 
{
	New_ID();
	Load(p_window, p_path);
}
Texture::Texture(Engine::Window* p_window, String p_path)
{
	New_ID();
	Load(p_window, p_path);
}

Texture::Texture() 
{
	New_ID();
}
Texture::~Texture()
{
	Destroy();
	m_window  = nullptr;
	center    = nullptr;
}


void Texture::New_ID()
{
	static int created_textures = 0;

	id = created_textures;
	created_textures++;
}

const SDL_Texture* Texture::operator()() const 
{
	return m_texture;
}
SDL_Texture* Texture::Get_SDL_Texture() const
{
	return m_texture;
}
Texture Texture::Get_Default()
{
	static bool once = true;

	if (once && m_window != NULL)
	{
		Text_File file(m_window->directory + "Locations.atlas");

		s_default_texture.Load(m_window, (m_window->imgs_dir + file.Read_After("NULLED_TEXTURE:")));
		once = false;
	}
	return s_default_texture;
}


bool Texture::Load(Engine::Window* p_window,  SDL_Texture* p_texture)
{
	Destroy();

	m_window  = p_window;
	m_texture = std::move(p_texture);

	if (m_texture == NULL)
	{
		return false;
	}
	return true;
}

bool Texture::Load(Engine::Window* p_window, std::string p_path) 
{
	return (Load(p_window, p_path.c_str()));
}
bool Texture::Load(Engine::Window* p_window, const char* p_path) 
{
	Destroy();

	path 	    = p_path;
	m_window    = p_window;
	m_texture   = Load_Texture_Static(p_window, p_path);
	m_pointing  = false;

	if (m_texture == NULL) 
	{
		Get_Default();
		m_texture  = s_default_texture.Get_SDL_Texture();
		m_pointing = true;

		return false;
	}
	return true;
}
bool Texture::Load_Mutable(Engine::Window* p_window, String p_path)
{
	Destroy();

	path 	    = p_path;
	m_window    = p_window;
	m_texture   = Load_Texture_Mutable(p_window, p_path.c_str(), pixels, pitch, size);
	m_pointing  = false;

	// Return to static.
	if (m_texture == NULL) 
	{
		Get_Default();
		m_texture  = s_default_texture.Get_SDL_Texture();
		m_pointing = true;

		return false;
	}
	return true;
}


// The Center parameter for rendercopyex is left NULL, i dont know how it works.
void Texture::Render(IRect p_rect, const SDL_Rect* p_clip) const
{
	SDL_RenderCopyEx(m_window->renderer, m_texture, p_clip, p_rect(), angle, center, flip);
}
void Texture::Render(FRect p_rect, const SDL_Rect* p_clip) const
{
	SDL_FPoint fpoint = {
		.x = static_cast<float>(center->x), 
		.y = static_cast<float>(center->y)
	};
	SDL_RenderCopyExF(m_window->renderer, m_texture, p_clip, p_rect(), angle, &fpoint, flip);
}
void Texture::Render(const SDL_Rect* p_rect, const SDL_Rect* p_clip) const
{
	SDL_RenderCopyEx(m_window->renderer, m_texture, p_clip, p_rect, angle, center, flip);
}
bool Texture::Lock()
{
	bool success = true;
    //Texture is already locked
    if(pixels != NULL)
    {
        m_window->log("Texture is already locked!", LOG_WARN);
        success = false;
    }
    //Lock texture
    else
    {
        if (SDL_LockTexture(m_texture, NULL, &pixels, &pitch) != 0)
        {
            m_window->log("Unable to lock texture!", LOG_ERROR);

            SDLU_Check_Error();
            success = false;
        } 
        // else true.
    }

    return success;
}
bool Texture::Unlock()
{
    bool success = true;

    //Texture is not locked
    if(pixels == NULL)
    {
        m_window->log("Texture is not locked!", LOG_WARN);
        success = false;
    }
    //Unlock texture
    else
    {
        SDL_UnlockTexture(m_texture);
        pixels = NULL;
        pitch = 0;
    }

    return success;
}

void Texture::Set_Opacity(Uint8 p_alpha) 
{
	SDL_SetTextureAlphaMod(m_texture, p_alpha);
}

void Texture::Set_Color(Color p_color) 
{
	SDL_SetTextureColorMod(m_texture, p_color.r, p_color.g, p_color.b);
}
void Texture::Set_Color(SDL_Color p_color) 
{
	SDL_SetTextureColorMod(m_texture, p_color.r, p_color.g, p_color.b);
}
void Texture::Set_Color(Uint8 p_red, Uint8 p_green, Uint8 p_blue)
{
	SDL_SetTextureColorMod(m_texture, p_red, p_green, p_blue);
}

void Texture::Destroy() 
{
	if (m_texture != NULL)
	{
		if (not(m_pointing))
		{
			SDL_DestroyTexture(m_texture); 
		}
		m_texture = nullptr;

		m_window->log.Add("Destroyed Texture: " + path, LOG_MSG);
	}
}


}