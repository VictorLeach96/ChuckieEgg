#include "header.h"

//-----Functions-----
//Picking
bool ce_player::checkPick(){

	//Loop through touching actors
	for (int i=0; i<touchActors.size(); i++){
		ce_actor *actor = touchActors[i];

		//Pick actor if it is pickable
		if (actor->pickable){
			actorPick(actor);
			return true;
		}
	}

	return false;
}
void ce_player::actorPick(ce_actor *actor){

	//Incriment score and remove actor from screen
	score += actor->points;
	actor->visible = false;

	//Play sound
	if (actor->type == cet_grain){
		play_sample(pick_grain,255,128,1000,0);
	}else if (actor->type == cet_egg){
		play_sample(pick_egg,255,128,1000,0);
	}
}
//Walking
void ce_player::walkLeft(){

	//Start walking
	if (!isWalkingLeft){
		isClimbing = false;
		isWalkingRight = false;
		isWalkingLeft = true;
		isClimbingUp = false;
		isClimbingDown = false;
		
		//Setup and start animation sequence
		stopAnimating();
		frame.size.height = 64;
		frame_y = 0;
		frame_sequence.clear();
		frame_sequence.push_back(3);
		frame_sequence.push_back(4);
		frame_sequence.push_back(3);
		frame_sequence.push_back(5);
		startAnimating();
	}

	//Walk
	moveLeft(player_speed);
}
void ce_player::walkRight(){

	//Start walking
	if (!isWalkingRight){
		isClimbing = false;
		isWalkingRight = true;
		isWalkingLeft = false;
		isClimbingUp = false;
		isClimbingDown = false;
		
		//Setup and start animation sequence
		stopAnimating();
		frame.size.height = 64;
		frame_y = 0;
		frame_sequence.clear();
		frame_sequence.push_back(0);
		frame_sequence.push_back(1);
		frame_sequence.push_back(0);
		frame_sequence.push_back(2);
		startAnimating();
	}

	//Walk
	moveRight(player_speed);
}

//Climbing
void ce_player::climbUp(){

	//Setup climbing
	if (!isClimbingUp){
		isClimbing = true;
		isWalkingRight = false;
		isWalkingLeft = false;
		isClimbingUp = true;
		isClimbingDown = false;
		
		//Setup and start animation sequence
		stopAnimating();
		frame.size.height = 72;
		frame_y = 384;
		frame_sequence.clear();
		frame_sequence.push_back(0);
		frame_sequence.push_back(1);
		frame_sequence.push_back(2);
		frame_sequence.push_back(1);
		startAnimating();

		//Snap to grid
		frame.cord.x = actorTouching(cet_ladder)->frame.cord.x;
	}

	//Climb
	moveUp(player_speed);
}
void ce_player::climbDown(){
	
	//Start climbing
	if (!isClimbingDown){
		isClimbing = true;
		isWalkingRight = false;
		isWalkingLeft = false;
		isClimbingUp = false;
		isClimbingDown = true;
		
		//Setup and start animation sequence
		stopAnimating();
		frame.size.height = 72;
		frame_y = 384;
		frame_sequence.clear();
		frame_sequence.push_back(0);
		frame_sequence.push_back(1);
		frame_sequence.push_back(2);
		frame_sequence.push_back(1);
		startAnimating();

		//Snap to grid
		frame.cord.x = actorTouching(cet_ladder)->frame.cord.x;
	}

	//Stop climbing if player has hit the floor
	if (isTouching(cet_wall)){
		isClimbingDown = false;
		isClimbing = false;
		stopAnimating();
		return;
	}

	//Climb
	moveDown(player_speed);
}

//Jumping
void ce_player::startJump(){

	//Start jumping
	if (!isJumping){
		isClimbing = false;
		isClimbingUp = false;
		isClimbingDown = false;
		isJumping = true;

		jumpCount = jump_height;
	}

	//Jump
	jump();
}
void ce_player::jump(){
	
	if (jumpCount == 0){

		//Jump down
		moveDown(jump_speed);

		//Stop jumping if collision with wall
		if (isTouching(cet_wall)){
			isJumping = false;
		}
	}else{

		//Jump up
		moveUp(jump_speed);
		jumpCount--;
	}
}