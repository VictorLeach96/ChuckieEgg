#include "header.h"

class ce_button{
public:

	//-----Constructor-----
	ce_button(int target){
		level = target;
	}

	//-----Destructor-----
	~ce_button(){
		destroy_bitmap(normal_bmp);
		destroy_bitmap(highlight_bmp);
	}
		
	//-----Properties-----
	ce_rect frame;
	int level;
	//Bitmap
	BITMAP *normal_bmp;
	BITMAP *highlight_bmp;
		
	//-----Functions------
	void setup(const char *nameC, ce_cord center);
	//Bitmap
	void blitWithMousePos(BITMAP *buffer, ce_cord mouse);
	bool isHovering(ce_cord mouse);
};