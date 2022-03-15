#pragma once
#define MAP_H
#define MAP_CLEAR_TEXTURES true

#include "Cpplib.h"
#include "Searcher.h"

#include "Window.h"
#include "Texture.h"
#include "Bitmap_Font.h"
#include "Graphic_Draw.h"
#include "File.h"


namespace Engine 
{
	struct Map_ILayer
	{
		Vector<String> 		 		  text_map    = {};
		Vector<String> 				  texture_map = {};

		Vector<char> 				  texture_representative = {};
		Vector<char> 				  text_representative    = {};

		// 2d. Type of texture/text and the actual rect.
		Vector<Vector<Graphic_IText>> texts        = {};
		Vector<Vector<IRect>>  		  texture_rect = {};
	};
	struct Map_FLayer
	{
		Vector<String> 		 		  text_map    = {};
		Vector<String> 				  texture_map = {};

		Vector<char> 				  texture_representative = {};
		Vector<char> 				  text_representative    = {};

		// 2d. Type of texture/text and the actual rect.
		Vector<Vector<Graphic_FText>> texts        = {};
		Vector<Vector<FRect>>  		  texture_rect = {};
	};


	// Textures and font, separated from layer to use again in separated layer.
	// Textures manipulation occurs in initialization.
	// Map layer start from 0.
	class Map_Structure 
	{
	public:
		Map_Structure(Engine::Window* p_window, int p_layers);
		~Map_Structure();

		int  Get_Layers_Size();
		void Load_Basic_Map(int p_layer, const char* p_map_path);
		void Load_Advanced_Map(int p_layer, const char* p_map_path);

		// In case you don't wanna create a file map.
		void Set_Texture_Map(int p_layer, Vector<String>& p_map);
		void Set_Text_Map(   int p_layer, Vector<String>& p_map);

		// Specify the letters you used to represent your textures/text in order to recognize corresponding pattern.
		// Text is different, not in order. You have to specify rect color etc.
		void Set_Text(int p_layer, char p_letter_representative, Engine::Bitmap_Font* p_font, const Graphic_IText& p_text);
		void Set_Texture(int p_layer, char p_letter_representative, Engine::Texture* p_texture, SDL_Rect* p_clip = NULL);

		// Will not dealocate after block.
		void Set_Text_Copy(int p_layer, char p_letter_representative, Engine::Bitmap_Font* p_font, const Graphic_IText& p_text);
		void Set_Texture_Copy(int p_layer, char p_letter_representative, Engine::Texture* p_texture, SDL_Rect* p_clip = NULL);
		void Set_Decoration(Engine::Texture* p_texture, Graphic_IRect* p_rect);

		// -Call this after you load the map and specified all corresponding representatives.
		// -Wil only be called if there is update.
		// -Sets specified texture/texts position in ordered manner.
		void Start_Ordering(IAxis p_start, ISize p_tilesize);

		void Render_Texts() const; 
		void Render_Textures() const;

		void Clear_Layer(int p_layer, bool p_destroy_texture = false);

	private:
		Engine::Window*       		  m_window;

		Vector<Map_ILayer> 			  m_layers;
		Vector<Engine::Bitmap_Font*>  m_fonts    = {};
		Vector<Engine::Texture*> 	  m_textures = {};

		Vector<Engine::Bitmap_Font*>  m_ptr_fonts    = {};
		Vector<Engine::Texture*>      m_ptr_textures = {};


		bool once = true;
	};

}

	/*class Map 
	{
	public:
		Map(void);
		~Map(void);

		virtual void Init(void);
		virtual void Create_Layer(unsigned short layers);

		virtual void Create(void);

		virtual void Render(unsigned short layer);
		virtual void Render_All(void);

		virtual void Camera(Character& character, unsigned short layer);
		virtual void Camera_All(Character& character);

		virtual void Events(void);
		virtual void Update(Character& character);

		virtual void Clear(unsigned short stage);
		virtual void Clear_All(void);

		virtual void Destroy(void);

	private:
		
		Vector<Map_Structure> m_structure;
		unsigned short m_layers;
	};

};*/

