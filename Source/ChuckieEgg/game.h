#include "header.h"

class ce_game{
	public:

		//-----Constructor-----
		ce_game(ce_level *lvl){
			isPlaying = false;
			hasWon = false;
			level = lvl;
			buffer = create_bitmap(SCREEN_W,SCREEN_H);

			//Timers
			animation = animation_speed;
			end_timer = 200;
			start_timer = 100;

			//Sounds
			walk = load_sample("walk.wav");
			walkSound = false;
			jump = load_sample("jump.wav");
			jumpSound = false;
			ladder = load_sample("ladder.wav");
			ladderSound = false;
			death = load_sample("death.wav");
			win = load_sample("win.wav");

			create_level();
		}

		//-----Destructor-----
		~ce_game(){
			destroy_bitmap(buffer);
			
			//Sounds
			destroy_sample(walk);
			destroy_sample(jump);
			destroy_sample(ladder);
			destroy_sample(death);
			destroy_sample(win);

			delete level;
		}
		
		//-----Properties-----
		bool isPlaying;
		bool hasWon;
		ce_level *level;
		BITMAP *buffer;
		//Timers
		int animation; //Tracks animation speed
		int end_timer; //Timer when games ended
		int start_timer; //Timer when games starts
		//Sounds
		SAMPLE *walk;
		SAMPLE *ladder;
		SAMPLE *death;
		SAMPLE *win;
		SAMPLE *jump;
		bool walkSound;
		bool jumpSound;
		bool ladderSound;

		//===Live Objects===
		ce_player *player;
		std::vector<ce_swan *> swans;
		
		//-----Functions------
		//Setup
		void create_level(); //Generate live objects from layout
		//Game Loop
		bool start_game(); //Start the game, returns whethe the game was won or not
		void checkEscape(); //Check if the player is pressing Esc or M to get out of the game
		void end_game(); //End the game and display the end screen
		//Logic
		void update(); //Update positions, movement, physics and AI
		void checkState(); //Check the game state and act accordingly to changes
		//Draw
		void drawStart(); //Draw the start screen
		void draw(); //Draw the game graphics
		void drawEnd(); //Draw the end screen
		void drawTitle(const char *name, ce_cord center); //Draw a title with given parameters
		//Sounds
		void playSounds(); //Play sounds dependant on keys being pressed
};