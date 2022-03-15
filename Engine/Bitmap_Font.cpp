#include "Bitmap_Font.h"


namespace Engine {

//___________________________________________________________________________________________________________________________________

std::map<char, SDL_Rect>* Bitmap_Font::s_share_alphabet = nullptr;

//___________________________________________________________________________________________________________________________________

Bitmap_Font::Bitmap_Font(Engine::Window* p_window, const char* p_path, std::vector<std::string> p_placement, ISize p_cut_size)
{
	Load(p_window, p_path);
	Configure_Placement(p_placement, p_cut_size);
}
Bitmap_Font::Bitmap_Font(Engine::Window* p_window, const char* p_path, const char* p_file_path)
{
	Load(p_window, p_path);
	Configure_Placement(p_file_path);
}
Bitmap_Font::Bitmap_Font(Engine::Window* p_window, const char* p_path, const char* p_file_path, const Graphic_IText& p_text, Text_IPosition& p_pos)
{
	Load(p_window, p_path);
	Configure_Placement(p_file_path);

	Preload_Text(p_text, p_pos);
}

Bitmap_Font::Bitmap_Font() : m_texture()
{
	m_window  = nullptr;
	m_texture = nullptr;

	id = m_texture->id;
}
//___________________________________________________________________________________________________________________________________
//
//
//___________________________________________________________________________________________________________________________________

Bitmap_Font::~Bitmap_Font() 
{
	// Deserted with error suppresion. Not to worry.
	Destroy();
	m_window = nullptr;
	s_share_alphabet = nullptr;
}
//___________________________________________________________________________________________________________________________________
//
//
//___________________________________________________________________________________________________________________________________


void Bitmap_Font::Load(Engine::Window* p_window, const char* p_path) 
{
	Destroy();

	m_window    = p_window;
	m_texture   = new Engine::Texture(p_window, p_path);
	m_is_loaded = true;

	id = m_texture->id;
}
void Bitmap_Font::Load(Engine::Window* p_window, std::string p_path) 
{
	Load(p_window, p_path.c_str());
}
//___________________________________________________________________________________________________________________________________
//
//
//___________________________________________________________________________________________________________________________________

void Bitmap_Font::Configure_Placement(std::vector<std::string> p_placement, ISize p_cut_size) 
{
	m_cut_size = p_cut_size;

	if (p_placement.empty())
	{
		ELog_Runtime("In Bitmap_Font::Configure_Placement(). placement is empty.", LOG_WARN);
		return;
	}
	if (p_cut_size.w < 0 || p_cut_size.h < 0)
	{
		ELog_Runtime("In Bitmap_Font::Configure_Placement(). cut size is unappropriate.", LOG_WARN);
		return;
	}

	for (int row = 0; row < p_placement.size(); row++) 
	{
		for (int letter = 0; letter < p_placement[row].size(); letter++) 
		{
			m_alphabet[p_placement[row][letter]] = {
				.x = letter * m_cut_size.w, 
				.y = row    * m_cut_size.h, 
				.w = m_cut_size.w, 
				.h = m_cut_size.h
			};

		}
	}

	s_share_alphabet = &m_alphabet;
}
//___________________________________________________________________________________________________________________________________
//
//
//___________________________________________________________________________________________________________________________________

void Bitmap_Font::Configure_Placement(const char* p_file_path)
{
	Text_File      file(p_file_path);
	Vector<String> placement;
	String         row_of_letters = file.Read_After("alphabet:");

	int w = To_Int(file.Read_After("width:"));
	int h = To_Int(file.Read_After("height:"));

	if (m_window == NULL)
	{
		ELog_Runtime("From Bitmap_Font::Configure_placement(). Window is NULL. Load first. first.", LOG_MSG);
		return;
	}
	m_window->log("Alphabet:",  LOG_MSG);

	while (row_of_letters != TFILE_TEXT_NOT_FOUND)
	{
		placement.push_back(row_of_letters); // includes beginning/.
		row_of_letters = file.Read_After(row_of_letters);

		m_window->log(row_of_letters, LOG_MSG);
	}
	// End of last row. Add blank
	placement.back() += ' ';

	// After extracting alphabet. Overloading function.
	Configure_Placement(placement, ISize{ w, h });
}
//___________________________________________________________________________________________________________________________________
//
//
//___________________________________________________________________________________________________________________________________

void Bitmap_Font::Preload_Text(const Graphic_IText& p_text, Text_IPosition& p_pos)
{
	std::map<char, SDL_Rect>::iterator it;

	m_texture->Set_Color(p_text.color);
	m_texture->Set_Opacity(p_text.alpha);

	// Determine Validity.
	if (not(p_pos.render_pos.empty()))
	{
		m_window->log("In Bitmap_Font::Preload_Text(). pos.render_pos is already loaded.", LOG_WARN);
	}
	if (not(p_pos.letter_pos.empty()))
	{
		m_window->log("In Bitmap_Font::Preload_Text(). pos.letter_pos is already loaded.", LOG_WARN);
	}

	// Main 
	for (int line = 0; line < p_text.content.size(); line++)
	{
		for (int letter = 0; letter < p_text.content[line].size(); letter++) 
		{
			// Render pos
			p_pos.render_pos.push_back(IRect{
				.x = p_text.rect.x + (p_text.rect.w * letter) + (p_text.space_margin * letter), 
				.y = p_text.rect.y + (p_text.rect.h * line)   + (p_text.newline_margin * line), 
				.w = p_text.rect.w, 
				.h = p_text.rect.h 
			}
			);

			// Clips Pos
			it = m_alphabet.find(p_text.content[line][letter]);
			p_pos.letter_pos.push_back(SDL_Rect{ it->second });// it->second = SDL_Rect(rect of of placement of alphabet).
		}
	}
}
//___________________________________________________________________________________________________________________________________
//
//
//___________________________________________________________________________________________________________________________________

void Bitmap_Font::Render_Prepared(const Text_IPosition& p_pos) const
{
	for (int letter = 0; letter < p_pos.render_pos.size(); letter++) 
	{
		m_texture->Render(p_pos.render_pos[letter], &p_pos.letter_pos[letter]);
	}

}
//___________________________________________________________________________________________________________________________________
//
//
//___________________________________________________________________________________________________________________________________

void Bitmap_Font::Render(const Graphic_IText& p_text) const
{
	std::map<char, SDL_Rect>::iterator it;

	for (int line = 0; line < p_text.content.size(); line++)
	{
		for (int letter = 0; letter < p_text.content[line].size(); letter++) 
		{
			IRect rect = IRect{
				.x = p_text.rect.x + (p_text.rect.w * letter) + (p_text.space_margin * letter), 
				.y = p_text.rect.y + (p_text.rect.h * line)   + (p_text.newline_margin * line), 
				.w = p_text.rect.w, 
				.h = p_text.rect.h
			};

			it = s_share_alphabet->find(p_text.content[line][letter]);
			m_texture->Render(rect, &it->second); // it->second = SDL_Rect(rect of of placement of alphabet).
		}
	}
}
//___________________________________________________________________________________________________________________________________
//
//
//___________________________________________________________________________________________________________________________________

void Bitmap_Font::Render(const Graphic_IText& p_text)
{
	std::map<char, SDL_Rect>::iterator it;

	m_texture->Set_Color(p_text.color);
	m_texture->Set_Opacity(p_text.alpha);

	for (int line = 0; line < p_text.content.size(); line++)
	{
		for (int letter = 0; letter < p_text.content[line].size(); letter++) 
		{
			IRect rect = IRect{
				.x = p_text.rect.x + (p_text.rect.w * letter) + (p_text.space_margin * letter), 
				.y = p_text.rect.y + (p_text.rect.h * line)   + (p_text.newline_margin * line), 
				.w = p_text.rect.w, 
				.h = p_text.rect.h
			};

			it = m_alphabet.find(p_text.content[line][letter]);
			m_texture->Render(rect, &it->second); // it->second = SDL_Rect(rect of of placement of alphabet).
		}
	}
}
//___________________________________________________________________________________________________________________________________
//
//

void Bitmap_Font::Destroy() 
{
	if (m_is_loaded)
	{
		delete m_texture;

		m_texture   = nullptr;
		m_is_loaded = false;
	}
}
//___________________________________________________________________________________________________________________________________











/*___________________________________________________________________________________________________________________________________
 *
 * 	 			OVERLOADING FLOAT TYPES OF:  Preload_Text(), Render_Prepared(), Render const(), and Render().
 *___________________________________________________________________________________________________________________________________*/

//___________________________________________________________________________________________________________________________________

void Bitmap_Font::Preload_Text(const Graphic_FText& p_text, Text_FPosition& p_pos)
{
	std::map<char, SDL_Rect>::iterator it;

	m_texture->Set_Color(p_text.color);
	m_texture->Set_Opacity(p_text.alpha);

	// Determine Validity.
	if (not(p_pos.render_pos.empty()))
	{
		m_window->log("In Bitmap_Font::Preload_Text(). pos.render_pos is already loaded.", LOG_WARN);
	}
	if (not(p_pos.letter_pos.empty()))
	{
		m_window->log("In Bitmap_Font::Preload_Text(). pos.letter_pos is already loaded.", LOG_WARN);
	}

	// Main 
	for (int line = 0; line < p_text.content.size(); line++)
	{
		for (int letter = 0; letter < p_text.content[line].size(); letter++) 
		{
			// Render pos
			p_pos.render_pos.push_back(FRect{
				.x = p_text.rect.x + (p_text.rect.w * letter) + (p_text.space_margin * letter), 
				.y = p_text.rect.y + (p_text.rect.h * line)   + (p_text.newline_margin * line), 
				.w = p_text.rect.w, 
				.h = p_text.rect.h 
			}
			);

			// Clips Pos
			it = m_alphabet.find(p_text.content[line][letter]);
			p_pos.letter_pos.push_back(SDL_Rect{ it->second });// it->second = SDL_Rect(rect of of placement of alphabet).
		}
	}
}
//___________________________________________________________________________________________________________________________________
//
//
//___________________________________________________________________________________________________________________________________

void Bitmap_Font::Render_Prepared(const Text_FPosition& p_pos) const
{
	for (int letter = 0; letter < p_pos.render_pos.size(); letter++) 
	{
		m_texture->Render(p_pos.render_pos[letter], &p_pos.letter_pos[letter]);
	}

}
//___________________________________________________________________________________________________________________________________
//
//
//___________________________________________________________________________________________________________________________________

void Bitmap_Font::Render(const Graphic_FText& p_text) const
{
	std::map<char, SDL_Rect>::iterator it;

	for (int line = 0; line < p_text.content.size(); line++)
	{
		for (int letter = 0; letter < p_text.content[line].size(); letter++) 
		{
			FRect rect = FRect{
				.x = p_text.rect.x + (p_text.rect.w * letter) + (p_text.space_margin * letter), 
				.y = p_text.rect.y + (p_text.rect.h * line)   + (p_text.newline_margin * line), 
				.w = p_text.rect.w, 
				.h = p_text.rect.h
			};

			it = s_share_alphabet->find(p_text.content[line][letter]);
			m_texture->Render(rect, &it->second); // it->second = SDL_Rect(rect of of placement of alphabet).
		}
	}
}
//___________________________________________________________________________________________________________________________________
//
//
//___________________________________________________________________________________________________________________________________

void Bitmap_Font::Render(const Graphic_FText& p_text)
{
	std::map<char, SDL_Rect>::iterator it;

	m_texture->Set_Color(p_text.color);
	m_texture->Set_Opacity(p_text.alpha);

	for (int line = 0; line < p_text.content.size(); line++)
	{
		for (int letter = 0; letter < p_text.content[line].size(); letter++) 
		{
			FRect rect = FRect{
				.x = p_text.rect.x + (p_text.rect.w * letter) + (p_text.space_margin * letter), 
				.y = p_text.rect.y + (p_text.rect.h * line)   + (p_text.newline_margin * line), 
				.w = p_text.rect.w, 
				.h = p_text.rect.h
			};

			it = m_alphabet.find(p_text.content[line][letter]);
			m_texture->Render(rect, &it->second); // it->second = SDL_Rect(rect of of placement of alphabet).
		}
	}
}
//___________________________________________________________________________________________________________________________________






//___________________________________________________________________________________________________________________________________
//					OTHER OVERLOADING For : Preload_Text()
//
//___________________________________________________________________________________________________________________________________



//___________________________________________________________________________________________________________________________________

void Bitmap_Font::Preload_Text(const Graphic_IText& p_text, Text_FPosition& p_pos)
{
	std::map<char, SDL_Rect>::iterator it;

	m_texture->Set_Color(p_text.color);
	m_texture->Set_Opacity(p_text.alpha);

	// Determine Validity.
	if (not(p_pos.render_pos.empty()))
	{
		m_window->log("In Bitmap_Font::Preload_Text(). pos.render_pos is already loaded.", LOG_WARN);
	}
	if (not(p_pos.letter_pos.empty()))
	{
		m_window->log("In Bitmap_Font::Preload_Text(). pos.letter_pos is already loaded.", LOG_WARN);
	}

	// Main 
	for (int line = 0; line < p_text.content.size(); line++)
	{
		for (int letter = 0; letter < p_text.content[line].size(); letter++) 
		{
			// Render pos
			p_pos.render_pos.push_back(FRect{
				.x = static_cast<float> (p_text.rect.x + (p_text.rect.w * letter) + (p_text.space_margin * letter)), 
				.y = static_cast<float> (p_text.rect.y + (p_text.rect.h * line)   + (p_text.newline_margin * line)), 
				.w = static_cast<float> (p_text.rect.w), 
				.h = static_cast<float> (p_text.rect.h) 
			}
			);

			// Clips Pos
			it = m_alphabet.find(p_text.content[line][letter]);
			p_pos.letter_pos.push_back(SDL_Rect{ it->second });// it->second = SDL_Rect(rect of of placement of alphabet).
		}
	}
}
//___________________________________________________________________________________________________________________________________
//
//
//___________________________________________________________________________________________________________________________________
void Bitmap_Font::Preload_Text(const Graphic_FText& p_text, Text_IPosition& p_pos)
{
	std::map<char, SDL_Rect>::iterator it;

	m_texture->Set_Color(p_text.color);
	m_texture->Set_Opacity(p_text.alpha);

	// Determine Validity.
	if (not(p_pos.render_pos.empty()))
	{
		m_window->log("In Bitmap_Font::Preload_Text(). pos.render_pos is already loaded.", LOG_WARN);
	}
	if (not(p_pos.letter_pos.empty()))
	{
		m_window->log("In Bitmap_Font::Preload_Text(). pos.letter_pos is already loaded.", LOG_WARN);
	}

	// Main 
	for (int line = 0; line < p_text.content.size(); line++)
	{
		for (int letter = 0; letter < p_text.content[line].size(); letter++) 
		{
			// Render pos
			p_pos.render_pos.push_back(IRect{
				.x = static_cast<int> (p_text.rect.x + (p_text.rect.w * letter) + (p_text.space_margin * letter)), 
				.y = static_cast<int> (p_text.rect.y + (p_text.rect.h * line)   + (p_text.newline_margin * line)), 
				.w = static_cast<int> (p_text.rect.w), 
				.h = static_cast<int> (p_text.rect.h) 
			}
			);

			// Clips Pos
			it = m_alphabet.find(p_text.content[line][letter]);
			p_pos.letter_pos.push_back(SDL_Rect{ it->second });// it->second = SDL_Rect(rect of of placement of alphabet).
		}
	}
}
}
