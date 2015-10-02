#include "header.h"

//Collisions
bool col_rectContainsPoint(ce_rect rect, ce_cord cord); //Detects whether point is in rect
bool col_rectIntersects(ce_rect rect1, ce_rect rect2); //Detects whether two rects intersect
ce_rect col_collisionFrame(ce_rect frame, ce_rect bounds); //Creates new frame with bounds

//Other
bool randomBool(); //Returns random boolean