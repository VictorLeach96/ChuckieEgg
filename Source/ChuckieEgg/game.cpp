#include "header.h"

//-----Tick timer-----
volatile int ticks = 0;
void ticker(){
	ticks++;
}
END_OF_FUNCTION(ticker)

//-----Functions-----
extern bool exit_bool;
//Init
void ce_game::create_level(){

	//Loop through each grid reference
	for (int row = 0; row<level->size.height ; row++){
		for (int col = 0; col<level->size.width ; col++){

			//Get object at grid reference
			int type = level->layout[row][col];
			ce_actor *object;

			//Create blank
			if (type == cet_blank){
				object = new ce_actor();
				object->type = cet_blank;
			//Create wall
			}else if (type == cet_wall){
				object = new ce_wall();
				object->type = cet_wall;
			//Cerate ladder
			}else if (type == cet_ladder){
				object = new ce_ladder();
				object->type = cet_ladder;
			//Create egg
			}else if (type == cet_egg){
				object = new ce_egg();
				object->type = cet_egg;
			//Create grain
			}else if (type == cet_grain){
				object = new ce_grain();
				object->type = cet_grain;
			//Create wall invisible
			}else if (type == cet_inv_wall){
				object = new ce_wall_inv();
				object->type = cet_inv_wall;
			}

			//Construct object
			object->frame.cord = makeCord(col * grid_w, row * grid_h);
			level->grid[row][col] = object;
		}
	}

	//Create player
	player = new ce_player();
	player->frame.cord = makeCord(level->start.x,level->start.y);
	player->level = level;
	player->clearAnimation();

	//Create swans and add to swan vector list
	for (int i=0; i<level->swans.size(); i++){
		ce_swan *swan = new ce_swan();
		swan->frame.cord = level->swans[i];
		swan->level = level;
		swan->clearAnimation();
		swans.push_back(swan);
		//Start in random direction
		if (randomBool()){
			swans[i]->walkLeft();
		}else{
			swans[i]->walkRight();
		}
	}
}

//Game Loop
bool ce_game::start_game(){
	//Create the tick timer functions
	LOCK_VARIABLE(ticks);
	LOCK_FUNCTION(ticker);
	install_int_ex(ticker, BPS_TO_TIMER(fps));

	//----------GameLoop----------
	while (isPlaying || end_timer > 0 || start_timer > 0){

		//Wait until a tick has happened
		while(ticks == 0){
			rest(1);
		}
		
		//If there is a tick pending update the logic and remve the tick
		while(ticks > 0){

			//Do game logic or decriment end/start timers
			if (isPlaying){
				checkEscape();
				update();
				checkState();
			}else if (start_timer >= 0){
				if (start_timer == 0){
					isPlaying = true;
					start_timer = -1;
				}else{
					start_timer--;
				}
			}else{
				end_timer--;
			}

			ticks--;
		}
		
		//Draw game or start/end screens
		if (start_timer > 0){
			drawStart();
		}else if (isPlaying || end_timer > 150){
			draw();
		}else{
			drawEnd();
		}
	}

	return hasWon;
}
void ce_game::checkEscape(){
	//Exit game
	if (key[KEY_ESC] || exit_bool){
		end_game();
		end_timer = 0;
	}
	//Goto menu
	if (key[KEY_M]){
		end_game();
	}
}
void ce_game::end_game(){
	isPlaying = false;

	//Stop sounds
	stop_sample(walk);
	stop_sample(jump);
	stop_sample(ladder);

	//Play ending sound
	if (hasWon){
		play_sample(win,255,128,1000,0);
	}else{
		play_sample(death,255,128,1000,0);
	}
}

//Logic
void ce_game::update(){

	//Tick swans
	for (int i=0; i<swans.size(); i++){
		swans[i]->ai_main();
	}

	//Vars
	bool gravity = true;
	bool action = false;

	//Start player jump
	if (key[KEY_SPACE] && !player->isJumping && player->isTouching(cet_wall)){
		player->startJump();
	}
	//Player is already jumping
	if (player->isJumping){

		//Stop playing jumping
		if ((key[KEY_W] || key[KEY_UP]) && player->isTouching(cet_ladder)){
			player->isJumping = false;

		}else{

			player->jump();

			//Perform player walking
			if (player->isWalkingLeft){
				player->walkLeft();
			}else if (player->isWalkingRight){
				player->walkRight();
			}

			action = true;
			gravity = false;

		}
	}

	//Climb Up
	if (!action){
		//Start climbing
		if ((key[KEY_W] || key[KEY_UP]) && player->isTouching(cet_ladder)){
			player->climbUp();
			action = true;
			gravity = false;
		}else{
			//Stop climbing
			if (!player->isTouching(cet_ladder) && player->isClimbing){
				player->isClimbing = false;
				player->isClimbingDown = false;
				player->isClimbingUp = false;
				gravity = true;
				action = true;
			}
			player->isClimbingUp = false;
		}
	}

	//Climb Down
	if (!action){
		if ((key[KEY_S] || key[KEY_DOWN]) && player->isTouching(cet_ladder) && !player->isTouching(cet_wall)){
			player->climbDown();
			action = true;
			gravity = false;
		}else{
			player->isClimbingDown = false;
		}
	}

	//Player Move left
	if (!action){
		if ((key[KEY_A] || key[KEY_LEFT])){
			player->walkLeft();
			action = true;
		}else{
			player->isWalkingLeft = false;
		}
	}

	//Player Move right
	if (!action){
		if ((key[KEY_D] || key[KEY_RIGHT])){
			player->walkRight();
			action = true;
		}else{
			player->isWalkingRight = false;
		}
	}

	//Still climbing
	if (!action){
		if (player->isClimbing){
			player->stopAnimating();
			action = true;
			gravity = false;
		}
	}

	//Apply gravity if not touching a ladder
	if (gravity && !player->isTouching(cet_ladder) && !player->isClimbing){
		player->moveDown(gravity_speed);
	}

	//Clear animation sequence if nothing else is happening
	if (!action){
		player->stopAnimating();
	}

	//Player pickups
	if (player->checkPick()){
		
		//Check if there are any more eggs left
		bool found = false;

		//Loop through each grid reference
		for (int i=0; i<level->grid.size(); i++){
			for (int l=0; l<level->grid[i].size(); l++){
				
				//Check if grid has egg
				ce_actor *actor = level->grid[i][l];
				if (actor->visible && actor->type == cet_egg){
					found = true;
				}
			}
		}

		//No eggs found
		if (!found){
			hasWon = true;
			end_game();
		}
	}

	//Swan pickups
	for (int i=0; i<swans.size(); i++){
		swans[i]->checkPick();
	}

	//Sounds
	playSounds();
}
void ce_game::checkState(){
	//Check if the player and swans collide
	ce_rect playerFrame = col_collisionFrame(player->frame,player->bounds);
	
	//Loop through each swan
	for (int i=0; i<swans.size(); i++){

		//Get swan collision frames
		ce_swan *swan = swans[i];
		ce_rect swanFrame = col_collisionFrame(swan->frame,swan->bounds);

		//Check for collision
		if (col_rectIntersects(swanFrame,playerFrame) && !invincible){
			end_game();
		}
	}

	//Check if player has fallen through map
	if (player->frame.cord.y > (grid_h * level->layout.size())){
		end_game();
	}
}

//Draw
void ce_game::drawStart(){
	//Clear buffer
	clear_to_color(buffer,makecol(0,0,0));

	//Draw title
	drawTitle(level->name,makeCord(screen->w/2,350));
	drawTitle("Arrow keys to move",makeCord(screen->w/2,500));
	drawTitle("Space to jump",makeCord(screen->w/2,600));

	//Draw
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}
void ce_game::draw(){
	clear_bitmap(buffer);

	//Draw grid of live objects
	for (int row = 0; row<level->size.height ; row++){
		for (int col = 0; col<level->size.width ; col++){
			level->grid[row][col]->blitToBitmap(buffer);
		}
	}

	//Animation ticker
	if (animation <= 0 && isPlaying){
		
		//Perform animations
		player->tickAnimation();
		for (int i=0; i<swans.size(); i++){
			swans[i]->tickAnimation();
		}

		animation = animation_speed;
	}else{
		animation--;
	}

	//Draw player
	player->blitToBitmap(buffer);

	//Draw swans
	for (int i=0; i<swans.size(); i++){
		ce_cord pos = swans[i]->getGridPosition();
		swans[i]->blitToBitmap(buffer);
	}

	//Draw grid if option enabled
	if (show_grid){
		for (int x=0; x<screen->w; x+=grid_w){
			for (int y=0; y<screen->h; y+=grid_h){
				rect(buffer,x,y,x+grid_w,y+grid_h,makecol(255,255,255));
			}
		}
	}

	//Construct score
	std::ostringstream stream;
	stream << "Score ";
	stream << player->score;
	string nameStr = stream.str();
	const char *nameC = nameStr.c_str();

	//Draw score
	BITMAP *score = create_bitmap(text_length(font, nameC),text_height(font));
	clear_to_color(score,makecol(0,0,0));
	textout_ex(score, font, nameC, 0, 0, makecol(240, 0, 240), -1);
	stretch_blit(score,buffer, 0,0,score->w, score->h, 20, 20,score->w * 4, score->h * 4);

	//Draw instructions
	const char *insC = "M = Menu & Esc = Quit";
	BITMAP *instructions = create_bitmap(text_length(font, insC),text_height(font));
	clear_to_color(instructions,makecol(0,0,0));
	textout_ex(instructions, font, insC, 0, 0, makecol(240, 0, 240), -1);
	stretch_blit(instructions,buffer, 0,0,instructions->w, instructions->h, ((screen->w)-instructions->w*4)-20, 20,instructions->w * 4, instructions->h * 4);

	//Draw screen
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}
void ce_game::drawEnd(){
	//Clear buffer
	clear_to_color(buffer,makecol(0,0,0));

	//Draw title
	const char *nameC;
	if (hasWon){
		nameC = "You Won!";
	}else{
		nameC = "Game Over!";
	}
	drawTitle(nameC,makeCord(screen->w/2,350));
	
	//Construct score
	std::ostringstream stream;
	stream << "You Scored ";
	stream << player->score;
	if (player->score >= 1000 || hasWon){
		stream << " whoop!";
	}else if (player->score >= 500){
		stream << " meh...";
	}else if (player->score >= 0){
		stream << " noob!";
	}
	string nameStr = stream.str();
	const char *scoreC = nameStr.c_str();

	//Draw score
	drawTitle(scoreC,makeCord(screen->w/2,550));

	//Draw
	blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}
void ce_game::drawTitle(const char *text, ce_cord center){
	//Draw a title dependant on parameters given
	BITMAP *bmp = create_bitmap(text_length(font, text),text_height(font));
	clear_to_color(bmp,makecol(0,0,0));
	textout_ex(bmp, font, text, 0, 0, makecol(240,0,240), -1);
	stretch_blit(bmp,buffer, 0,0,bmp->w, bmp->h, center.x - ((bmp->w*5)/2), center.y - ((bmp->h*5)/2),bmp->w * 5, bmp->h * 5);
	destroy_bitmap(bmp);
}
//Sounds
void ce_game::playSounds(){

	//Walk sound if not already playing
	if ((key[KEY_A] || key[KEY_D] || key[KEY_LEFT] || key[KEY_RIGHT]) && (player->isWalkingLeft || player->isWalkingRight) && !jumpSound){
		if (!walkSound){
			walkSound = true;
			play_sample(walk,255,128,1000,10000);
		}
	}else{
		walkSound = false;
		stop_sample(walk);
	}

	//Ladder sound if not already playing
	if ((key[KEY_W] || key[KEY_S] || key[KEY_UP] || key[KEY_DOWN]) && player->isClimbing && !jumpSound){
		if (!ladderSound){
			ladderSound = true;
			play_sample(ladder,255,128,1000,10000);
		}
	}else{
		ladderSound = false;
		stop_sample(ladder);
	}

	//Jump sound if not already playing
	if (player->isJumping){
		if (!jumpSound){
			jumpSound = true;
			play_sample(jump,255,128,1000,10000);
		}
	}else{
		jumpSound = false;
		stop_sample(jump);
	}
}