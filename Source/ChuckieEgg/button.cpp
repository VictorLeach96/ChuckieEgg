#include "header.h"

//Functions
void ce_button::setup(const char *nameC, ce_cord center){

	//Calculate size of the text frame
	frame.size.width = text_length(font,nameC) * 4;
	frame.size.height = text_height(font) * 4;
	frame.cord.x = center.x - (frame.size.width / 2);
	frame.cord.y = center.y - (frame.size.height / 2);

	//Create bitmaps for normal and highlight buttons
	normal_bmp = create_bitmap(frame.size.width,frame.size.height);
	highlight_bmp = create_bitmap(frame.size.width,frame.size.height);
	clear_to_color(normal_bmp,makecol(0,0,0));
	clear_to_color(highlight_bmp,makecol(0,0,0));

	//Construct normal bitmap
	BITMAP *temp = create_bitmap(text_length(font, nameC),text_height(font));
	clear_to_color(temp,makecol(0,0,0));
	textout_ex(temp, font, nameC, 0, 0, makecol(240, 0, 240), -1);
	stretch_blit(temp,normal_bmp, 0,0,temp->w, temp->h, 0, 0,frame.size.width, frame.size.height);
	destroy_bitmap(temp);
			
	//Construct highlight bitmap
	BITMAP *temp2 = create_bitmap(text_length(font, nameC),text_height(font));
	clear_to_color(temp2,makecol(0,0,0));
	textout_ex(temp2, font, nameC, 0, 0, makecol(255, 255, 0), -1);
	stretch_blit(temp2,highlight_bmp, 0,0,temp->w, temp->h, 0, 0,frame.size.width, frame.size.height);
	destroy_bitmap(temp2);
}

//Bitmap
void ce_button::blitWithMousePos(BITMAP *buffer, ce_cord mouse){

	//Display correct bitmap depending on whether mouse is hovering over button
	if (isHovering(mouse)){
		blit(normal_bmp,buffer,0,0,frame.cord.x,frame.cord.y,normal_bmp->w,normal_bmp->h);
	}else{
		blit(highlight_bmp,buffer,0,0,frame.cord.x,frame.cord.y,highlight_bmp->w,highlight_bmp->h);
	}
}
bool ce_button::isHovering(ce_cord mouse){

	//Return whether moues is over the button
	if (col_rectContainsPoint(frame,mouse)){
		return true;
	}else{
		return false;
	}
}