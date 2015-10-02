#include "header.h"

extern bool exit_bool;

//Functions
void ce_menu::setupMenu(){
	int y = 460;

	//Loop through each level and create a button
	for (int i=0; i<5; i++){

		//Construct button name
		std::stringstream buttonNameC;
		buttonNameC << "Play Level " << i+1;
		string buttonName = buttonNameC.str();

		//Create level button with name and position
		ce_button *button = new ce_button(i+1);
		button->setup(buttonName.c_str(),makeCord(screen->w/2,y));
		buttons.push_back(button);

		y+=70;
	}

	//Create the quit button
	ce_button *button_q = new ce_button(-1);
	button_q->setup("Quit Game",makeCord(screen->w/2,screen->h-90));
	buttons.push_back(button_q);
}
void ce_menu::showMenu(){

	//-----Menu Loop-----
	while(1){
		//Exit game
		if (key[KEY_ESC] || exit_bool){
			return;
		}

		//Clear buffer
		clear_to_color(buffer,makecol(0,0,0));

		//Draw title
		drawText("Chuckie Egg", makecol(0,255,0),makeCord(screen->w/2,70),6);
		drawText("Victor Leach", makecol(0,255,0),makeCord(screen->w/2,140),6);

		//Draw instructions
		drawText("- Collect the eggs -",makecol(0,255,255),makeCord(screen->w/2,250),4);
		drawText("- Pickup the seeds -",makecol(0,255,255),makeCord(screen->w/2,300),4);
		drawText("- Avoid the swans -",makecol(0,255,255),makeCord(screen->w/2,350),4);

		//Draw buttons
		for (int i=0; i<buttons.size(); i++){
			ce_button *button = buttons[i];

			//Draw button to the buffer
			button->blitWithMousePos(buffer,makeCord(mouse_x,mouse_y));
			
			//Check if butotn has been clicked and is hover over
			if (mouse_b & 1){
				if (button->isHovering(makeCord(mouse_x,mouse_y))){
					//Decide whether level target is telling it to quit or to start the level
					if (button->level == -1){
						return;
					}else{
						playLevel(button->level);
					}
				}
			}
		}

		//Draw Draw mouse and buffer to the screen
		blit(mouse,buffer,0,0,mouse_x,mouse_y,mouse->w,mouse->h);
		blit(buffer,screen,0,0,0,0,buffer->w, buffer->h);
	}
}
void ce_menu::playLevel(int lvl){

	//Construct level filename
	std::stringstream filename;
	filename << "level_" << lvl << ".txt";

	//Create new level
	ce_level *level = new ce_level();
	level->load_file(filename.str());

	//Construct level name
	std::stringstream nameC;
	nameC << "Level " << lvl;
	string name = nameC.str();
	level->name = name.c_str();

	//Start level
	ce_game *game = new ce_game(level);
	bool hasWon = game->start_game();
	delete game;
	//If the level was successful then play the next level
	if (hasWon && lvl < 5){
		playLevel(lvl + 1);
	}
}
void ce_menu::drawText(const char *text, int colour, ce_cord center, int size){

	//Create a text bitmap from the given values
	BITMAP *bmp = create_bitmap(text_length(font, text),text_height(font));
	clear_to_color(bmp,makecol(0,0,0));
	textout_ex(bmp, font, text, 0, 0, colour, -1);
	stretch_blit(bmp,buffer, 0,0,bmp->w, bmp->h, center.x - ((bmp->w*size)/2), center.y - ((bmp->h*size)/2),bmp->w * size, bmp->h * size); //Draw the text at a larger size and center the cord
	destroy_bitmap(bmp);
}