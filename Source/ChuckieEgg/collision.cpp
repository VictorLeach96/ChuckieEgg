#include "header.h"

//Collisions
bool col_rectContainsPoint(ce_rect rect, ce_cord cord){
	//Check X and Y axis for intersection
	if (cord.x > rect.cord.x && cord.x < rect.cord.x + rect.size.width){
		if (cord.y > rect.cord.y && cord.y < rect.cord.y + rect.size.height){
			return true;
		}
	}

	return false;
}
bool col_rectIntersects(ce_rect rect1, ce_rect rect2){
	//Check if rectangle is out of bounds of each other, if not they must be touching
	if (rect1.cord.x + rect1.size.width < rect2.cord.x
		|| rect1.cord.y + rect1.size.height < rect2.cord.y
		|| rect1.cord.x > rect2.cord.x + rect2.size.width
		|| rect1.cord.y > rect2.cord.y + rect2.size.height){
		return false;
	}else{
		return true;
	}
}
ce_rect col_collisionFrame(ce_rect frame, ce_rect bounds){
	//Create collision frame from frame and bounds given
	ce_rect colFrame = frame;

	colFrame.cord.x += bounds.cord.x;
	colFrame.cord.y += bounds.cord.y;
	colFrame.size.height = bounds.size.height;
	colFrame.size.width = bounds.size.width;

	return colFrame;
}

//Other
bool randomBool(){
	//Create random int and return true/false whether it is 0 or 1
	int random = rand() % 2;
	if (random == 0){
		return true;
	}else{
		return false;
	}
}