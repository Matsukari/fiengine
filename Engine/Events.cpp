#include "Events.h"


namespace Engine
{

Events::Events(SDL_Event& p_event)
{
	is_key_down   = false;
	is_key_up     = false;
	is_same_key   = false;

	current_key = SDLK_BACKSPACE;
	prev_key    = SDLK_BACKSPACE;
	key_repeats = 0;

	key_held_time   = 0;
	key_unheld_time   = 0;

	keypress_history.resize(31, 0);
	keypress_index    = 0;


	// Maouse Parts //
	is_mouse_up   = false;
	is_mouse_down = false;

	// Mouse position //
	mouse_pos  	    = IAxis{ 0, 0 };
	mouse_start_pos = IAxis{ 0, 0 };
	mouse_end_pos   = IAxis{ 0, 0 };
	wheel 			= IAxis{ 0, 0 }; 

	mouse_held_time   = 0;
	mouse_unheld_time = 0;

	// History //
	mousebutton_history.resize(31, 0);
	mousepos_history.resize(31, IAxis{0,0});

	// Indexes //
	mousebutton_index = 0;
	mousepos_index    = 0;


	// text Input parts //
	text = {""};
	cur_line = 0;
	has_newline = false;

	event 	   = &p_event;
	cursor_img = nullptr;

	m_first_key   = false;
	m_first_mouse = false;

	m_last_key   = 0;
	m_last_mouse = 0;

	m_hold_start_t = DEFAULT_KEY_HOLD_START_TIME;
	m_repeat_end_t = DEFAULT_KEY_REPEAT_END_TIME;
}
Events::~Events()
{
	event = nullptr;
	window = nullptr;

	cursor_img->Destroy();
}
const SDL_Event* Events::operator()() const
{
	return event;
}
SDL_Event* Events::Get_Event() const
{
	return event;
}

void Events::Set_Key_Hold_Start_Time(Uint32 p_ms)
{
	m_hold_start_t = p_ms;
}
void Events::Set_Key_Repeat_End_Time(Uint32 p_ms)
{
	m_repeat_end_t = p_ms;
}
bool Events::Set_Input_Cursor(Window* p_window, Texture* p_texture)
{
	if (p_texture == NULL)
	{
		p_window->log("In Events::Set_Input_Cursor(), p_texture(arg) is NULL...Defaulting cursor_img to default.", LOG_ERROR);
		cursor_img->Load(p_window, "Default");

		return false;
	}
	window = p_window;

	cursor_img->Destroy();
	bool result = cursor_img->Load(p_window, p_texture->Get_SDL_Texture());

	return result;
}


void Events::Start_Text_Input()
{
	SDL_StartTextInput();
}
void Events::Stop_Text_Input()
{
	SDL_StopTextInput();
}

const SDL_MouseButtonEvent& Events::Mouse_Button() const
{
	return event->button;
}


void Events::Handle_Mouse()
{
	// Mouse events
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		is_mouse_down = true;
		is_mouse_up   = false;

		mouse_start_pos = mouse_pos;
		m_last_mouse = SDL_GetTicks();

		// Add to history //
		mousepos_history[ mousepos_index ] = mouse_pos;
		mousebutton_history[ mousebutton_index ] = event->button.button;

		++mousepos_index;
		++mousebutton_index;
	}
	else if (event->type == SDL_MOUSEBUTTONUP)
	{
		is_mouse_up   = true;
		is_mouse_down = false;

		mouse_end_pos = mouse_pos;
		m_last_mouse = SDL_GetTicks();
	}
	else
	{
		is_mouse_up   = false;
	}

	// Check only if is scrolling. The SDl's wheel will remain the smae until change of any course.
	if (event->type == SDL_MOUSEWHEEL)
	{
		wheel.x = event->wheel.x;
		wheel.y = event->wheel.y;
	}
	else
	{
		wheel.x = 0;
		wheel.y = 0;
	}
}
void Events::Handle_Keyboard()
{
	// Key Events
	// Every keydown, restarts last held time.
	if (event->type == SDL_KEYDOWN)
	{
		is_key_down = true;
		is_key_up   = false;

		prev_key = current_key;
		current_key = event->key.keysym.sym;

		// Add to history //
		keypress_history[ keypress_index ] = current_key;
		++keypress_index; // goto 0 after limit(31).

		// If your HOLDING //
		if (event->key.repeat == 0)
		{
			m_last_key = SDL_GetTicks();
		} 
		// If you pressed the SAME KEY simutaneously //
		if ((prev_key == current_key) && (key_unheld_time != 0 && key_unheld_time < m_repeat_end_t))
		{
			key_repeats++;
		}
		else
			key_repeats = 0;
	}
	else if (event->type == SDL_KEYUP)
	{
		is_key_up   = true;
		is_key_down = false;

		m_last_key  = SDL_GetTicks();
	}
	else
		is_key_up = false;

}
void Events::Handle_Text_Input()
{
	// Add inputted text.
	if (event->type == SDL_TEXTINPUT)
	{
		text[cur_line] += event->text.text;

	} // If input BACKSLASH(delete).
	else if ((event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_BACKSPACE) && text.size() > 0)
	{
		// letter takes precedence over newline
		// if current text in line has letters to delete.
		if (text[cur_line].size() > 0)
		{
			text[cur_line].pop_back();
		}
		else if (has_newline)
		{
			text.pop_back();
			has_newline = false;
			cur_line--;
		} 
	} // Only workds in right keypad.
	else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_KP_ENTER)
	{
		cur_line++;
		has_newline = true;

		text.push_back(String{""});
	}
}

void Events::Handle_All()
{
	Handle_Mouse();
	Handle_Keyboard();
	Handle_Text_Input();
}
void Events::Update()
{
	SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

	// Check continously.
	// Keyboad
	// when you hold a key, SDL_KEYDOWN will trigger every aprox. 20ms
	if (is_key_down)
	{
		Uint32 hold_time = (SDL_GetTicks() - m_last_key);

		// Until time exceed the given start for hold time.
		if (hold_time > m_hold_start_t)
		{
			// Erase the time when your holding until start.
			key_held_time = hold_time - m_hold_start_t;
		}
		key_unheld_time = 0;
	}
	else // Unheld time
	{
		key_held_time   = 0;
		key_unheld_time = (SDL_GetTicks() - m_last_key);
	}

	// Mouse 
	if (is_mouse_down)
	{
		mouse_held_time   = (SDL_GetTicks() - m_last_mouse);
		mouse_unheld_time = 0;
	}
	else // unheld time
	{
		mouse_held_time   = 0;
		mouse_unheld_time = (SDL_GetTicks() - m_last_mouse);
	}

}

}