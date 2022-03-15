#include "Map.h"


namespace Engine 
{

	Map_Structure::Map_Structure(Engine::Window* p_window, int p_layers)
	{
		m_window = p_window;
		m_layers = {};
		m_layers.resize(p_layers);
	}
	Map_Structure::~Map_Structure()
	{
		m_window = nullptr;

		// Allocated textures
		for (auto &texture : m_textures)
		{
			delete texture;
			texture = nullptr;
		}
		for (auto &font : m_fonts)
		{
			delete font;
			font = nullptr;
		}
		// Pointing textures
		for (auto &texture : m_ptr_textures)
		{
			texture = nullptr;
		}
		for (auto &font : m_ptr_fonts)
		{
			font = nullptr;
		}
	}
	int Map_Structure::Get_Layers_Size()
	{
		return m_layers.size();
	}


	void Map_Structure::Load_Basic_Map(int p_layer, const char* p_path)
	{
		Vector<String> content = File_To_Vector(p_path);
	}
	void Map_Structure::Load_Advanced_Map(int p_layer, const char* p_path)
	{
		return;
	}

	void Map_Structure::Set_Texture_Map(int p_layer, Vector<String>& p_map) 
	{
		m_layers[p_layer].texture_map = p_map;
	}
	void Map_Structure::Set_Text_Map(int p_layer, Vector<String>& p_map) 
	{
		m_layers[p_layer].text_map = p_map;
	}

	void Map_Structure::Set_Text(int p_layer, char p_letter_representative, Engine::Bitmap_Font* p_font, const Graphic_IText& p_text)
	{
		// If it is not yet in Set. Create a group of block rects for this texture.
		if (Search_Char(p_letter_representative, m_layers[p_layer].text_representative, Range_Equal(m_layers[p_layer].text_representative)) == SEARCH_FAILED)
		{
			m_layers[p_layer].text_representative.push_back(p_letter_representative);
			m_layers[p_layer].texts.push_back(Vector<Graphic_IText>());

			m_fonts.push_back(std::move(p_font));
			p_font = nullptr;

			m_fonts.back()->id = p_layer;
		}

		m_layers[p_layer].texts.back().push_back(p_text);
	}
	void Map_Structure::Set_Texture(int p_layer, char p_letter_representative, Engine::Texture* p_texture, SDL_Rect* p_clip)
	{
		bool repre_in_layer;
		int  textr_in_layer;

		// Search all layers if representative or texture existed.
		for (auto &layer : m_layers)
		{
			repre_in_layer = Search_Char(p_letter_representative, layer.texture_representative, Range_Equal(layer.text_representative));
		}
		textr_in_layer = Search_ID(p_texture->id, m_textures, Range_Equal(m_textures));


		// If it is not yet in any layer. Create a group of block rects for this texture.
		if (not(repre_in_layer) && (textr_in_layer == SEARCH_FAILED))
		{
			m_layers[p_layer].texture_representative.push_back(p_letter_representative);
			m_layers[p_layer].texture_rect.push_back(Vector<IRect>());

			m_textures.push_back(std::move(p_texture));
			p_texture = nullptr;

			m_textures.back()->id = p_layer;
		}
	}


	void Map_Structure::Set_Text_Copy(int p_layer, char p_letter_representative, Engine::Bitmap_Font* p_font, const Graphic_IText& p_text)
	{

	}
	void Map_Structure::Set_Texture_Copy(int p_layer, char p_letter_representative, Engine::Texture* p_texture, SDL_Rect* p_clip) 
	{
		// If it is not yet in Set. Create a group of block rects for this texture.
		if (Search_Char(p_letter_representative, m_layers[p_layer].texture_representative, Range_Equal(m_layers[p_layer].texture_representative)) == SEARCH_FAILED)
		{
			m_layers[p_layer].texture_representative.push_back(p_letter_representative);
			m_layers[p_layer].texture_rect.push_back(Vector<IRect>());

			m_textures.push_back(nullptr);
			m_textures.back() = p_texture;

			m_textures.back()->id = p_layer;
		}
	}
	void Map_Structure::Set_Decoration(Engine::Texture* p_texture, Graphic_IRect* p_rect)
	{

	}
	void Map_Structure::Start_Ordering(IAxis p_start, ISize p_tilesize) 
	{
		// Position of rect carries .
		int x = p_start.x;
		int y = p_start.y;

		// Destroy previous build.
		for (auto &layer : m_layers)
		{
			for (int texture = 0; texture < layer.texture_rect.size(); texture++)
			{
				layer.texture_rect[texture].clear();
			}
		}

		for (auto &layer : m_layers)
		{
			// Loop every row of letters.
			for (int row = 0; row < layer.texture_map.size(); row++)
			{
				// Loop every letters.
				for (int letter = 0; letter < layer.texture_map[row].size(); letter++)
				{
					// loop to Check if current letter is similar to representative:  (i = looping representatives/ texture)
					for (int i = 0; i < layer.texture_representative.size(); i++)
					{
						// If bullseye, Set the X and Y of the corresponding representative.
						if (layer.texture_map[row][letter] == layer.texture_representative[i]) 
						{
							layer.texture_rect[i].push_back(IRect{ 
								.x = x, 
								.y = y, 
								.w = p_tilesize.w, 
								.h = p_tilesize.h
							});
							m_window->log("Ordered Position: " + std::to_string(x) + " " + std::to_string(y), LOG_MSG);
						}
					}
					 // Every individual letters. Go Right.
					x += p_tilesize.w;
				}
				// Every rows. Go Down from in leftmost.
				x  = p_start.x;
				y += p_tilesize.h;

			}

			// Reset and check again for text_map in layer.
			x = p_start.x; 
			y = p_start.y; 
		}

	}
	void Map_Structure::Render_Texts() const
	{
		for (int font = 0; font < m_fonts.size(); font++)
		{
			for (auto layer : m_layers)
			{
				for (int i = 0; i < layer.texts.size(); i++)
				{
					m_fonts[font]->Render(layer.texts[font][i]);
				}
			}
		}
	}
	void Map_Structure::Render_Textures() const
	{
		for (int texture = 0; texture < m_textures.size(); texture++)
		{
			for (auto layer : m_layers)
			{
				for (int i = 0; i < layer.texture_rect[texture].size(); i++)
				{
					m_textures[texture]->Render(layer.texture_rect[texture][i]);
				}
			}
		}
	}
	void Map_Structure::Clear_Layer(int p_layer, bool p_destroy_texture) 
	{
		m_layers[p_layer].text_map.clear();
		m_layers[p_layer].texture_map.clear();

		m_layers[p_layer].text_representative.clear();
		m_layers[p_layer].texture_representative.clear();

		m_layers[p_layer].texts.clear();
		m_layers[p_layer].texture_rect.clear();

		// Destroy Textures in given layer.
		if (p_destroy_texture)
		{
			// Search all the textures in given layer.
			Vector<int>  layer_textures = Give_Matching_ID(p_layer, m_textures, Range_Equal(m_textures));
			Vector<int>  layer_fonts    = Give_Matching_ID(p_layer, m_fonts, Range_Equal(m_fonts));

			// If there is textures in given layer. destroy it.
			if (not(layer_textures.empty()))
			{
				for (auto i : layer_textures)
				{
					delete m_textures[ i ];
					m_textures[ i ] = nullptr;
				}
			}
			if (not(layer_fonts.empty()))
			{
				for (auto i : layer_fonts)
				{
					delete m_fonts[ i ];
					m_fonts[ i ] = nullptr;
				}
			}
		}
	}


}

/*	void Map::Init(void)
	{
		m_layers = 0;
	}
	void Map::Create_Layer(unsigned short layers) 
	{
		m_structure.resize(layers);
	}
	void Map::Create(void) 
	{
		return;
	}


	void Map::Render(unsigned short layer) 
	{
		m_structure[layer].Render_Texture();
	}
	void Map::Render_All(void) {
		for (unsigned short i = 0; i < m_structure.size(); i++)
			m_structure[i].Render_Texture();
	}


	void Map::Update(Character& character) {
		return;
	}


	void Map::Camera(Character& character, unsigned short layer) 
	{
		m_structure[layer].Camera(character);
	}
	void Map::Camera_All(Character& character) {
		for (unsigned short i = 0; i < m_structure.size(); i++)
		{
			m_structure[i].Camera(character);
		}
	}


	void Map::Events(void) 
	{
		return;
	}

	void Map::Clear(unsigned short layer) 
	{ 
		m_structure[layer].Clear();
	}

	void Map::Clear_All(void) 
	{ 
		for (unsigned short i = 0; i < m_structure.size(); i++){
			m_structure[i].Clear();
		}
	}


	void Map::Destroy(void) 
	{
		for (unsigned short i = 0; i < m_structure.size(); i++){
			m_structure[i].Destroy_Texture();
		}
	}

};*/