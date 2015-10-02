#include "header.h"

class ce_object{
public:

	//-----Constructor-----
	ce_object(){
		solid = false;
		visible = false;

		//Geometry
		frame = makeRect(0,0,grid_w,grid_h);
		bounds = makeRect(0,0,frame.size.width,frame.size.height);
		offset = makeCord(0,0);

		//Bitmap
		bmp = create_bitmap(frame.size.width,frame.size.height);
		clear_to_color(bmp,makecol(0,0,0));
	}

	//-----Destructor-----
	~ce_object(){
		destroy_bitmap(bmp);
	}
		
	//-----Properties-----
	bool solid;
	bool visible;
	//Geometry
	ce_rect frame;
	ce_rect bounds;
	ce_cord offset;
	//Bitmap
	BITMAP *bmp;

	//-----Functions-----
	//Geometry
	ce_cord getGridPosition(); //Returns the current grid cord of the object
	//Bitmap
	void blitToBitmap(BITMAP *bitmap); //Draw the object to a bitmap
};