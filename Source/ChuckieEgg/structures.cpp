#include "header.h"

//Functions
ce_cord makeCord(double x, double y){
	ce_cord cord;
	cord.x = x;
	cord.y = y;
	return cord;
}
ce_size makeSize(double width, double height){
	ce_size size;
	size.width = width;
	size.height = height;
	return size;
}
ce_rect makeRect(double x, double y, double width, double height){
	ce_rect rect;
	rect.cord = makeCord(x,y);
	rect.size = makeSize(width,height);
	return rect;
}