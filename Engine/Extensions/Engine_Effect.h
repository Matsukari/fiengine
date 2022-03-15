#pragma once
#define ENGINE_EFFECT_H

#include "../Window.h"
#include "../Texture.h"
#include "../Sound.h"

#define EFFECT_ON   1
#define EFFECT_OFF  0


namespace Engine
{
struct Effect_Status
{
	// public
	int     status 		= EFFECT_OFF;
	int     speed 		= 0;
	int     encores 	= 0;

	// protected
	int     cur_replays = 0;
	int 	cur_frame 	= 0;
	Uint32  lasttime 	= 0;
};

class Effect
{
public:
	Effect(Engine::Window* p_window, Engine::Texture* p_texture, Engine::Sound* p_sound, Vector<SDL_Rect> p_clips);
	Effect();
	~Effect();

	// Allocated.
	void Set(     Engine::Window* p_window, Engine::Texture* p_texture, Engine::Sound* p_sound, Vector<SDL_Rect> p_clips);
	void Set_Copy(Engine::Window* p_window, Engine::Texture* p_texture, Engine::Sound* p_sound, Vector<SDL_Rect> p_clips);

	void Play(Effect_Status&   e, int p_speed, int p_encores = 0);
	void Update(Effect_Status& e);
	void Render(const Effect_Status& e, IRect p_rect) const;
	void Render(const Effect_Status& e, FRect p_rect) const;

	void Destroy();

public:
	Engine::Window*     window;
	Engine::Texture*    texture;
	Engine::Sound*      sound;

	Vector<SDL_Rect>    clips;

	bool is_allocated = false;
};

}