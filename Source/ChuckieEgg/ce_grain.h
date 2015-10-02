#include "header.h"

class ce_grain : public ce_actor{
	public:

		//-----Constructor-----
		ce_grain() : ce_actor(){
			solid = false;
			visible = true;
			pickable = true;
			points = 50;

			//Create bitmap
			BITMAP *source = load_bitmap("blocks.bmp",NULL);
			stretch_blit(source, bmp, 0, 24, 16, 8, 0, 0, frame.size.width, frame.size.height);
			destroy_bitmap(source);

			//Setup bounds
			bounds.cord.x = 24;
			bounds.size.width = 16;
		}

		//-----Properties-----

		//-----Functions-----
};