#include "header.h"

//-----Functions----
//Animation
void ce_pawn::clearAnimation(){
	clear_bitmap(bmp);

	//Check if animation sequence has been specified
	if (frame_sequence.size() == 0){
		//Blit first frame
		blit(source,bmp,0,0,0,0,frame.size.width,frame.size.height);
	}else{
		//Blit first frame of the a animatoin sequence
		int y_pos = frame_sequence[0] * frame.size.height;
		blit(source,bmp,0,frame_y + y_pos,0,0,frame.size.width,frame.size.height);
	}
}
void ce_pawn::startAnimating(){
	//Reset animation values and blit first tick
	isAnimating = true;
	frame_current = 0;
	tickAnimation();
}
void ce_pawn::tickAnimation(){
	if (isAnimating){

		//Check if ticks is more than there are number of frames
		if (frame_current >= frame_sequence.size()){
			frame_current = 0;
		}

		//Get the current frames y position
		int y_pos = frame_sequence[frame_current] * frame.size.height;
		frame_current++;

		//Draw frame at y position
		blit(source,bmp,0,frame_y + y_pos,0,0,frame.size.width,frame.size.height);
	}
}
void ce_pawn::stopAnimating(){
	//Stop animating and rest the current frame
	isAnimating = false;
	frame_current = 0;
	clearAnimation();
}

//Collision
bool ce_pawn::collisionForRect(ce_rect rect){

	//Rest touching actors and collision
	touchActors.clear();
	isColide = false;

	//Loop through each object and run collision detection on them
	for (int row = 0; row<level->size.height ; row++){
		for (int col = 0; col<level->size.width ; col++){

			//Get the two objects and get their collision frame
			ce_actor *actor = level->grid[row][col];
			ce_rect playerFrame = col_collisionFrame(rect,bounds);
			
			//Check whether the two objects colide
			if (collisionForObject(actor,playerFrame)){
				
				//Check if actor is touching an invisible wall (This is to stop swans from going out of bounds)
				if (actor->type == cet_inv_wall){
					isColide = true;
				}

				//Add touching actors to vector
				if (actor->visible){
					touchActors.push_back(actor);
				}

				//Return true (has colided) if solid
				if (actor->solid){
					return true;
				}
			}
		}
	}

	return false;
}
bool ce_pawn::collisionForObject(ce_actor *object,ce_rect rect){

	//Calculate collision frames based on bounds of object
	ce_rect objFrame = col_collisionFrame(object->frame, object->bounds);

	//Detect collision
	if (col_rectIntersects(rect,objFrame)){
		return true;
	}else{
		return false;
	}
}
bool ce_pawn::isTouching(grid_type type){

	//Loop through touching objects and compare to type given
	for (int i=0; i<touchActors.size(); i++){
		if (touchActors[i]->type == type){
			return true;
		}
	}
	return false;
}
ce_actor* ce_pawn::actorTouching(grid_type type){

	//Loop through touching objects and compare to type given and return live object
	for (int i=0; i<touchActors.size(); i++){
		if (touchActors[i]->type == type){
			return touchActors[i];
		}
	}
	return new ce_actor();
}

//Movement
void ce_pawn::updateFrame(ce_rect newFrame){

	//Check level bounds
	if (newFrame.cord.x < -2 || newFrame.cord.y < 0 || newFrame.cord.x + 2 + newFrame.size.width > screen->w || newFrame.cord.y + newFrame.size.height > screen->h){
		return;
	}

	//Check collision and apply new frame if none found
	if (!collisionForRect(newFrame)){
		frame = newFrame;
	}
}
void ce_pawn::moveLeft(float speed){

	//Construct new cordinate
	ce_rect newFrame = frame;
	newFrame.cord.x -= speed;
	updateFrame(newFrame);
}
void ce_pawn::moveRight(float speed){

	//Construct new cordinate
	ce_rect newFrame = frame;
	newFrame.cord.x += speed;
	updateFrame(newFrame);
}
void ce_pawn::moveUp(float speed){

	//Construct new cordinate
	ce_rect newFrame = frame;
	newFrame.cord.y -= speed;
	updateFrame(newFrame);
}
void ce_pawn::moveDown(float speed){

	//Construct new cordinate
	ce_rect newFrame = frame;
	newFrame.cord.y += speed;
	updateFrame(newFrame);
}