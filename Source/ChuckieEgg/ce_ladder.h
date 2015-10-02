#include "header.h"

class ce_ladder : public ce_actor{
	public:

		//-----Constructor-----
		ce_ladder() : ce_actor(){
			solid = false;
			visible = true;

			//Create bitmap
			BITMAP *source = load_bitmap("blocks.bmp",NULL);
			stretch_blit(source, bmp, 0, 8, 16, 8, 0, 0, frame.size.width, frame.size.height);
			destroy_bitmap(source);

			//Setup bounds
			bounds.cord.x = 24;
			bounds.size.width = 16;
		}

		//-----Properties-----

		//-----Functions-----
};