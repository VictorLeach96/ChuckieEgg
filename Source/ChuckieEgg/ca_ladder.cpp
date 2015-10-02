#include "header.h"

class ce_ladder : public ce_object{
	public:

		//-----Constructor-----
		ce_ladder() : ce_object(){
			BITMAP *source = load_bitmap("blocks.bmp",NULL);
			stretch_blit(source, bmp, 0, 8, 16, 8, 0, 0, frame.width, frame.height);
			destroy_bitmap(source);

			bounds.cord.y = 1;
			bounds.height = 5;
		}

		//-----Destructor-----
		~ce_ladder(){
	
		}

		//-----Properties-----

		//-----Functions-----
};