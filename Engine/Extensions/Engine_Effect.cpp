#include "Engine_Effect.h"


namespace Engine
{

Effect::Effect(Engine::Window* p_window, Engine::Texture* p_texture, Engine::Sound* p_sound, Vector<SDL_Rect> p_clips)
{
	Set(p_window, p_texture, p_sound, p_clips);
}
Effect::Effect()
{
	Set_Copy(nullptr, nullptr, nullptr, Vector<SDL_Rect>{});
}
Effect::~Effect()
{
	Destroy();
}

void Effect::Set(Engine::Window* p_window, Engine::Texture* p_texture, Engine::Sound* p_sound, Vector<SDL_Rect> p_clips)
{
	Destroy();

	window    = p_window;
	texture   = std::move(p_texture);
	sound     = std::move(p_sound);
	clips     = p_clips;


	p_texture = nullptr;
	p_sound   = nullptr;

	is_allocated = true;
}
void Effect::Set_Copy(Engine::Window* p_window, Engine::Texture* p_texture, Engine::Sound* p_sound, Vector<SDL_Rect> p_clips)
{
	Destroy();

	window    = p_window;
	texture   = p_texture;
	sound     = p_sound;
	clips     = p_clips;

	is_allocated = false;
}
void Effect::Play(Effect_Status& e, int p_speed, int p_encores)
{
	// Only play after finishing current one.
	if (e.status == EFFECT_OFF) 
	{
		e.status  =  EFFECT_ON;

		e.encores = p_encores;
		e.speed   = p_speed;

		sound->Play();
	}
}
void Effect::Update(Effect_Status& e)
{
	static uint32_t time = 0;
					time = SDL_GetTicks();

	if ((e.status == EFFECT_ON) && (time > e.lasttime + e.speed))
	{
		e.lasttime = time;
		e.cur_frame++;

		if (e.cur_frame >= clips.size())
		{
			sound->Play();

			e.cur_frame = 0;
			e.cur_replays++;

			// If the number of replays is greater than or equal the provided times of replays. Turn if off.
			if (e.cur_replays > e.encores) 
			{
				e.cur_replays = 0;
				e.status      = EFFECT_OFF;
			}
		}
	}
}
void Effect::Render(const Effect_Status& e, IRect rect) const
{
	if (e.status == EFFECT_ON) 
	{
		texture->Render(rect, &clips[e.cur_frame]);
	}
}
void Effect::Render(const Effect_Status& e, FRect rect) const
{
	if (e.status == EFFECT_ON) 
	{
		texture->Render(rect, &clips[e.cur_frame]);
	}
}

void Effect::Destroy()
{
	if (is_allocated)
	{
		delete texture;
		delete sound;
	}
	window  = nullptr;
	texture = nullptr;
	sound   = nullptr;
}

}