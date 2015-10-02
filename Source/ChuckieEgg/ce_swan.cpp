#include "header.h"

//-----Functions-----
void ce_swan::action(){

	//Climbing
	if (isClimbingUp){
		climbUp();
		return;
	}
	if (isClimbingDown){
		climbDown();
		return;
	}

	//Walking
	if (isWalkingLeft){
		walkLeft();
		return;
	}
	if (isWalkingRight){
		walkRight();
		return;
	}
}
bool ce_swan::isClimbing(){
	//Check if swan is climbing
	if (isClimbingUp || isClimbingDown){
		return true;
	}else{
		return false;
	}
}
bool ce_swan::isWalking(){
	//Check if swan is walking
	if (isWalkingLeft || isWalkingRight){
		return true;
	}else{
		return false;
	}
}
//AI
void ce_swan::ai_main(){
	ce_cord pos = getGridPosition();

	//Bounce off bounds
	if (pos.x == 0){
		walkRight();
		return;
	}
	if (pos.x == 19){
		walkLeft();
		return;
	}

	//Get adjasent objects
	left = cet_blank;
	right = cet_blank;
	topLeft = cet_blank;
	topRight = cet_blank;
	bottom = level->layout[pos.y+1][pos.x];
	top = level->layout[pos.y-1][pos.x];

	//Left bounds
	if (pos.x != 0){
		left = level->layout[pos.y+1][pos.x-1];
		topLeft = level->layout[pos.y][pos.x-1];
	}
	//Right bounds
	if (pos.x != 19){
		right = level->layout[pos.y+1][pos.x+1];
		topRight = level->layout[pos.y][pos.x+1];
	}

	//Colide with invisible walls
	if (isWalkingLeft && isColide){
		walkRight();
		return;
	}else if (isWalkingRight && isColide){
		walkLeft();
		return;
	}

	//-----Decision AI-----
	//If swan reaches top of ladder then climb back down
	if (isClimbingUp && isBlank(top)){
		climbDown();
	}
	//Change direction if swan detects no more platforms
	if (isWalkingLeft && isBlank(left)){
		walkRight();
		return;
	}
	if (isWalkingRight && isBlank(right)){
		walkLeft();
		return;
	}
	//Detect whether swan is able to climb up or down a ladder and start climbing
	if (isWalking() && isTouching(cet_ladder) && hasLeftLadder && !hasJumpedOffLadder){
		hasJoinedLadder = false;
		hasLeftLadder = false;
		if (bottom == cet_wall && left == cet_wall && right == cet_wall){
			if (randomBool()){
				climbUp();
				return;
			}
		}else{
			ai_climb();
			return;
		}
	}
	//Detect if swan is climbing and has hit bottom of the ladder, then start walking
	if (isClimbing() && bottom == cet_wall && hasLeftFloor){
		hasLeftFloor = false;
		ai_walk();
		return;
	}
	//Detect if swan has passed a floor point while climbing and make a decision whether or not to carry on climbing or jump off
	if (isClimbing() && (left == cet_wall || right == cet_wall) && hasJoinedLadder && hasLeftFloor && !hasJumpedOffLadder){
		hasJoinedLadder = false;
		if (randomBool()){
			hasJumpedOffLadder = true;
			ai_walk();
			return;
		}
	}

	//UUpdate AI events
	if (!isTouching(cet_ladder) && isWalking()){
		hasLeftLadder = true;
		hasJoinedLadder = false;
	}
	if (bottom != cet_wall && isClimbing()){
		hasLeftFloor = true;
	}
	if (hasJumpedOffLadder && bottom == cet_wall && isWalking()){
		hasJumpedOffLadder = false;
	}
	if (bottom == cet_ladder && top == cet_ladder && left != cet_wall && right != cet_wall && isClimbing() && !hasJoinedLadder){
		hasJoinedLadder = true;
	}

	//Apply gravity if not climbing
	if (!isClimbing() && hasLeftLadder){
		moveDown(gravity_speed);
	}
	
	//Perform actions
	action();
}
void ce_swan::ai_walk(){
	//Walk in random direction
	if (randomBool()){
		walkLeft();
	}else{
		walkRight();
	}
}
void ce_swan::ai_climb(){
	//Climb in random direction
	if (randomBool()){
		climbUp();
	}else{
		climbDown();
	}
}
bool ce_swan::isBlank(int var){
	//Check if actor type is blank
	if (var == cet_blank || var == cet_egg || var == cet_egg){
		return true;
	}else{
		return false;
	}
}
//Picking
void ce_swan::checkPick(){

	//Loop through touching actors and pick ones that are pickable
	for (int i=0; i<touchActors.size(); i++){
		ce_actor *actor = touchActors[i];

		//If the actor is a grain and is pickable then remove it from the screen
		if (actor->pickable && actor->type == cet_grain){
			actor->visible = false;
			return;
		}
	}
}
//Actions
void ce_swan::climbUp(){

	//Start climbing
	if (!isClimbingUp){
		isClimbingUp = true;
		isClimbingDown = false;
		isWalkingLeft = false;
		isWalkingRight = false;

		startClimb = true;
		
		//Setup and start animation sequence
		stopAnimating();
		frame_sequence.clear();
		frame_sequence.push_back(4);
		frame_sequence.push_back(5);
		startAnimating();

		//Snap to grid
		frame.cord.x = actorTouching(cet_ladder)->frame.cord.x + 1;
	}

	//Walk
	moveUp(enemy_speed);
}
void ce_swan::climbDown(){

	//Start climbing
	if (!isClimbingDown){
		isClimbingUp = false;
		isClimbingDown = true;
		isWalkingLeft = false;
		isWalkingRight = false;

		startClimb = true;
		
		//Setup and start animation sequence
		stopAnimating();
		frame_sequence.clear();
		frame_sequence.push_back(4);
		frame_sequence.push_back(5);
		startAnimating();

		//Snap to grid
		frame.cord.x = actorTouching(cet_ladder)->frame.cord.x + 1;
	}

	//Walk
	moveDown(enemy_speed);
}
void ce_swan::walkLeft(){

	//Start walking
	if (!isWalkingLeft){
		isClimbingUp = false;
		isClimbingDown = false;
		isWalkingLeft = true;
		isWalkingRight = false;
		
		startWalk = true;
		
		//Setup and start animation sequence
		stopAnimating();
		frame_sequence.clear();
		frame_sequence.push_back(2);
		frame_sequence.push_back(3);
		startAnimating();
	}

	//Walk
	moveLeft(enemy_speed);
}
void ce_swan::walkRight(){

	//Start walking
	if (!isWalkingRight){
		isClimbingUp = false;
		isClimbingDown = false;
		isWalkingLeft = false;
		isWalkingRight = true;
		
		startWalk = true;
		
		//Setup and start animation sequence
		stopAnimating();
		frame_sequence.clear();
		frame_sequence.push_back(0);
		frame_sequence.push_back(1);
		startAnimating();
	}

	//Walk
	moveRight(enemy_speed);
}