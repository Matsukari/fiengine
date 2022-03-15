#include "Spritesheet.h"

void Extract_Spritesheet(Vector<SDL_Rect>& vector, Sprite_Extract_Info sprite, short frames) 
{
	SDL_Rect frame_box;
	int      extracted = 0;

	// For exact cut.
	int bottom_edge = (sprite.cut.h * (sprite.sheet.h / sprite.cut.h));
	int right_edge  = (sprite.cut.w * (sprite.sheet.w / sprite.cut.w));

	for (int col = sprite.start.y; col <= bottom_edge; col += sprite.cut.h) 
	{
		for (int row = sprite.start.x; row <= right_edge; row += sprite.cut.w) 
		{
			switch (sprite.order)
			{
				case ORDER_LEFT_TO_RIGHT:
					frame_box = {row, col, sprite.cut.w, sprite.cut.h};
					break;
				case ORDER_TOP_TO_BOTTOM:
					frame_box = {col, row, sprite.cut.w, sprite.cut.h};
					break;

				default:
					ELog_Runtime("Provided argument for (Extract Order) unidentified.", LOG_ERROR);
					break;
			}

			vector.push_back(frame_box);
			extracted++;

			if (extracted >= frames)
				return;
		}
	}
}
void Extract_Spritesheet(Vector<SDL_Rect>& vector, const char* sprite_path) 
{
	std::ifstream   infile(sprite_path);
	String          name;
	IAxis           start;
	ISize           sheet;
	ISize           cut;
	EXTRACT_ORDER  order;

	int 			frames;

	infile >> name >> start.x >> start.y;
	infile >> name >> sheet.w >> sheet.h;
	infile >> name >> cut.w   >> cut.h;
	infile >> name >> name;

	if (name == "left_to_right")
	{
		order = ORDER_LEFT_TO_RIGHT;
	}
	else if (name == "top_to_bottom")
	{
		order = ORDER_TOP_TO_BOTTOM;
	}
	else
	{
		ELog_Runtime((String)"Unidentified String in file: " + sprite_path, LOG_ERROR);
	}

	infile >> name >> frames;
	infile.close();


	Extract_Spritesheet(vector, Sprite_Extract_Info{start, sheet, cut, order}, frames);
}
