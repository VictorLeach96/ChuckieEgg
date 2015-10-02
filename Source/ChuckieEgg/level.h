#include "header.h"

class ce_level{
	public:

		//-----Constructor-----
		ce_level(){
			isLoaded = false;
			name = "Level";

			//Set grid size
			layout.resize(27,std::vector<int>(20,0));
			grid.resize(27,std::vector<ce_actor*>(20,0));
		}

		//-----Destructor-----
		~ce_level(){
			//Remove grid
			layout.clear();
			for (int row = 0; row<size.height ; row++){
				for (int col = 0; col<size.width ; col++){
					delete grid[row][col];
				}
			}
		}
		
		//-----Properties-----
		//Prototype
		const char *name; //Name which is displayed at start of the level
		bool isLoaded; //Check if the level object has been initialised
		ce_cord start; //Bitmap cord position of the player start
		std::vector<ce_cord> swans; //Bitmap cord position of the swans
		ce_size size; //Level size in width and height

		//Matrix
		std::vector< std::vector<int> > layout; //Bitmap of the level layout
		std::vector< std::vector<ce_actor*> > grid; //Live objects in the level

		//-----Functions------
		void load_file(std::string filename); //Get the level text from a file
		void decode_text(std::string text); //Create the object from level text
};