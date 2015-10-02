#include "header.h"

class ce_pawn : public ce_object{
	public:

		//-----Constructor-----
		ce_pawn() : ce_object(){
			solid = true;
			visible = true;
			isColide = false;

			//Setup bounds
			frame.size.height = 64;
			bounds.size.height = frame.size.height;

			//Recreate bmp at different size
			destroy_bitmap(bmp);
			bmp = create_bitmap(frame.size.width, frame.size.height);

			//Setup animation
			isAnimating = false;
			frame_current = 0;
			frame_y = 0;
		}

		//Deconstructor
		~ce_pawn(){
			destroy_bitmap(source);
			frame_sequence.clear();
			touchActors.clear();
		}

		//-----Properties-----
		ce_level *level;
		bool isColide; //Shows whether the pawn is touching an invisible wall
		std::vector<ce_actor *> touchActors; //Actors which are currently touching the pawn
		//Animation
		BITMAP *source; //Animation sprite sheet
		bool isAnimating;
		int frame_current; //Current frame in the animation sheet
		int frame_y; //Y offset in the sprite sheet
		std::vector<int> frame_sequence; //Chosen frames from the sprite sheet

		//-----Functions-----
		//Animation
		void clearAnimation(); //Reset animation sequence and update default bitmap
		void startAnimating(); //Begin a new animation sequence
		void tickAnimation(); //Run every tick and update frame
		void stopAnimating(); //Stop the animation sequence
		//Collision
		bool collisionForRect(ce_rect rect); //Checks whether self colides with given rect
		bool collisionForObject(ce_actor *object,ce_rect rect); //Checks whether object colides with rect
		bool isTouching(grid_type type); //Returns whether pawn is touching a actor type
		ce_actor* actorTouching(grid_type type); //Returns the live actor which is being touched
		//Movement
		void updateFrame(ce_rect newFrame); //Do appropriate collision checking and update the frame
		void moveLeft(float speed); //Move left at speed
		void moveRight(float speed); //Move right at speed
		void moveUp(float speed); // Move up at speed
		void moveDown(float speed); //Move down at speed
};