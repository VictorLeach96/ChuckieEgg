#include "header.h"

class ce_menu{
	public:

		//-----Constructor-----
		ce_menu(){
			buffer = create_bitmap(screen->w, screen->h);
			mouse = create_bitmap(24,24);
			clear_to_color(mouse,makecol(240,0,240));
		}

		//-----Destructor-----
		~ce_menu(){
			destroy_bitmap(buffer);
			destroy_bitmap(mouse);

			//Remove buttons
			for (int i=0; i<buttons.size(); i++){
				delete buttons[i];
			}
		}
		
		//-----Properties-----
		std::vector<ce_button *> buttons;
		//Bitmap
		BITMAP *buffer;
		BITMAP *mouse;
		
		//-----Functions------
		void setupMenu();
		void showMenu();
		void playLevel(int level);
		void drawText(const char *text, int colour, ce_cord center, int size);
};