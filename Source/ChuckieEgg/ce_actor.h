#include "header.h"

class ce_actor : public ce_object{
	public:

		//-----Constructor-----
		ce_actor() : ce_object(){
			pickable = false;
			points = 0;
		}

		//-----Properties-----
		grid_type type;
		bool pickable;
		int points;

		//-----Functions------
};