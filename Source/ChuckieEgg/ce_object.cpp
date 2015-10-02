#include "header.h"

//-----Functions-----
ce_cord ce_object::getGridPosition(){
	//Get the current cord
	ce_cord cord = frame.cord;

	//Change origin of cord
	cord.x += frame.size.width / 2;
	cord.y += frame.size.height - (frame.size.height / 4);

	//Divide cords by grid and remove decimal points
	cord.x = floor(cord.x / grid_w);
	cord.y = floor(cord.y / grid_h);

	return cord;
}
void ce_object::blitToBitmap(BITMAP *bitmap){

	//Draw object to bitmap if visible
	if (visible){
		masked_blit(bmp,bitmap, 0, 0, offset.x + frame.cord.x, offset.y + frame.cord.y, frame.size.width, frame.size.height);
	}

	//Draw collision frame around object if turned on
	if (show_bounds && solid){
		rect(bmp,bounds.cord.x,bounds.cord.y,bounds.cord.x + bounds.size.width, bounds.cord.y + bounds.size.height,makecol(255,255,255));
	}
}