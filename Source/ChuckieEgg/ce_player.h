#include "header.h"

class ce_player : public ce_pawn{
	public:
		
		//-----Constructor-----
		ce_player() : ce_pawn(){
			solid = true;
			visible = true;
			score = 0;

			//Actions
			isClimbing = false;
			isClimbingUp = false;
			isClimbingDown = false;
			isWalkingRight = false;
			isWalkingLeft = false;
			isJumping = false;

			//Setup bitmap
			BITMAP *original = load_bitmap("player.bmp",NULL);
			source = create_bitmap(original->w * 4, original->h * 4);
			stretch_blit(original, source, 0, 0, original->w, original->h, 0, 0, source->w, source->h);
			destroy_bitmap(original);

			//Setup bounds
			bounds.cord.x = 8;
			bounds.size.width = 48;
			bounds.size.height = 62;
			
			//Setup Sounds
			pick_egg = load_sample("pick_egg.wav");
			pick_grain = load_sample("pick_grain.wav");
		}

		//-----Destructor-----
		~ce_player(){
			//Remove sounds
			destroy_sample(pick_egg);
			destroy_sample(pick_grain);
		}

		//-----Properties-----
		int score;
		//Actions
		bool isWalkingLeft;
		bool isWalkingRight;
		bool isClimbing;
		bool isClimbingUp;
		bool isClimbingDown;
		bool isJumping;
		int jumpCount; //Current jumping position
		//Sounds
		SAMPLE *pick_egg;
		SAMPLE *pick_grain;

		//-----Functions-----
		//Picking
		bool checkPick(); //Check whether there is a pickable object touching player
		void actorPick(ce_actor *actor); //Pick a specific actor
		//Walking
		void walkLeft();
		void walkRight();
		//Climbing
		void climbUp();
		void climbDown();
		//Jumping
		void startJump();
		void jump();
};