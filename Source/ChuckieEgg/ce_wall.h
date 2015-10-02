#include "header.h"

class ce_wall : public ce_actor{
	public:

		//-----Constructor-----
		ce_wall() : ce_actor(){
			solid = true;
			visible = true;

			//Create bitmap
			BITMAP *source = load_bitmap("blocks.bmp",NULL);
			stretch_blit(source, bmp, 0, 0, 16, 8, 0, 0, frame.size.width, frame.size.height);
			destroy_bitmap(source);

			//Setup bounds
			bounds.cord.x = 0;
			bounds.cord.y = 4;
			bounds.size.height = 20;
			bounds.size.width = 63;
		}

		//-----Properties-----

		//-----Functions-----
};