#pragma once
#define EVENTS_H

#include "Cpplib.h"

#include "SDLU.h"
#include "Window.h"
#include "Texture.h"
#include "Bitmap_Font.h"

// SDL_MouseButtonEvent is not flipped until command.
#define WHEEL_DOWN -1
#define WHEEL_UP    1
#define DEFAULT_KEY_HOLD_START_TIME   100
#define DEFAULT_KEY_REPEAT_END_TIME   500


namespace Engine
{
class Events
{
public:
	Events(SDL_Event& p_event);
	~Events();

	const SDL_Event* operator()() const;
		  SDL_Event* Get_Event() const;

	void Set_Key_Hold_Start_Time(Uint32 p_ms);
	void Set_Key_Repeat_End_Time(Uint32 p_ms);
	bool Set_Input_Cursor(Window* p_window, Texture* p_texture);

	void Start_Text_Input();
	void Stop_Text_Input();

	const SDL_MouseButtonEvent& Mouse_Button() const;

	// Occurs non-continiously, only after MOUSEBUTTONUP, safe to say, only once after button is up. Also within up.
	virtual void Handle_Mouse();
	virtual void Handle_Keyboard();
	virtual void Handle_Text_Input();

	void Handle_All();
	virtual void Update();

public:
	// Keyboard Parts //
	// default is 0 //
	bool is_key_down;
	bool is_key_up;
	bool is_same_key;

	SDL_Keycode current_key;
	SDL_Keycode prev_key;
	Uint32 		key_repeats;

	Uint32 key_held_time;
	Uint32 key_unheld_time;

	Vector<SDL_Keycode> keypress_history; // If current index is in limits, reset(roll back) and overwite the beginning //
	size_t keypress_index : 5; // 31 //


	// Mouse Parts //
	bool is_mouse_up;
	bool is_mouse_down;

	// Position //
	IAxis mouse_pos;
	IAxis mouse_start_pos; // Position of mouse within pressing. Remain until hold agin.//
	IAxis mouse_end_pos; // Position of mouse after pressing. Remain until hold agin.//
	IAxis wheel;  // WHEEL_DOWN or WHEEL_UP

	Uint32 mouse_held_time;
	Uint32 mouse_unheld_time;

	Vector<Uint8>  mousebutton_history;
	Vector<IAxis>  mousepos_history;
	size_t mousebutton_index : 5; // 31 //
	size_t mousepos_index : 5; // 31 //


	// Text Input Parts //
	Vector<String> text;
	size_t cur_line;
	bool   has_newline;

public:
	SDL_Event* event;
	Window*    window;
	Texture*   cursor_img;

private:
	// The time when fisrst held. diminish when upheld
	bool m_first_key;
	bool m_first_mouse;

	Uint32 m_last_key;
	Uint32 m_last_mouse;

	Uint32 m_hold_start_t;
	Uint32 m_repeat_end_t;
};

}