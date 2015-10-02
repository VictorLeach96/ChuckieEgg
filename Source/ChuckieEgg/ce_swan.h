#include "header.h"

class ce_swan : public ce_pawn{
	public:

		//-----Constructor-----
		ce_swan() : ce_pawn(){
			solid = true;
			visible = true;

			//AI
			lastPos = makeCord(0,0);
			left = cet_blank;
			right = cet_blank;
			topLeft = cet_blank;
			topRight = cet_blank;
			top = cet_blank;
			bottom = cet_blank;
			startWalk = false;
			startClimb = false;
			hasLeftLadder = true;
			hasLeftFloor = true;
			hasJumpedOffLadder = false;
			hasJoinedLadder = false;

			//Actions
			isClimbingUp = false;
			isClimbingDown = false;
			isWalkingRight = false;
			isWalkingLeft = false;

			//Setup image
			BITMAP *original = load_bitmap("swans.bmp",NULL);
			source = create_bitmap(original->w * 4, original->h * 4);
			stretch_blit(original, source, 0, 0, original->w, original->h, 0, 0, source->w, source->h);
			destroy_bitmap(original);

			//Setup bounds
			frame.size.height = 80;
			frame.size.width = 56;
			offset.y = -16;
			offset.x = 2;
			bounds.size.height = frame.size.height-16;
			bounds.size.width = frame.size.width;

			//Recreate bmp
			destroy_bitmap(bmp);
			bmp = create_bitmap(frame.size.width,frame.size.height);
		}

		//-----Properties-----

		//AI
		ce_cord lastPos;
		int left;
		int right;
		int top;
		int bottom;
		int topRight;
		int topLeft;
		bool startWalk;
		bool startClimb;
		bool hasLeftLadder;
		bool hasLeftFloor;
		bool hasJumpedOffLadder;
		bool hasJoinedLadder;
		//Actions
		bool isClimbingUp;
		bool isClimbingDown;
		bool isWalkingRight;
		bool isWalkingLeft;

		//-----Functions-----
		void action(); //Perform action which was decided by the ai main
		bool isClimbing(); //Check if swan is climbing
		bool isWalking(); //Check if swan is walking
		//AI
		void ai_main(); //Decide what AI to perform
		void ai_climb(); //Climb in random direction
		void ai_walk(); //Walk in random direction
		bool isBlank(int var); //Check if current position is blank
		//Picking
		void checkPick(); //Check and pick and grains which swan is on
		//Actions
		void climbUp();
		void climbDown();
		void walkLeft();
		void walkRight();
};