#include "header.h"

class ce_platform{
	public:

		//-----Constructor-----
		ce_platform(){
			//Create bitmap for the platform
			bitmap = create_bitmap(64,32);

			//Load section of the bitmap into the object
			BITMAP *source = load_bitmap("blocks.bmp",NULL);
			stretch_blit(source, bitmap, 0, 0, 16, 8, 0, 0, 64, 32);
			destroy_bitmap(source);
		}

		//-----Destructor-----
		~ce_platform(){
			destroy_bitmap(bitmap);
		}
		
		//-----Properties-----
		BITMAP *bitmap;

		//-----Functions------
};