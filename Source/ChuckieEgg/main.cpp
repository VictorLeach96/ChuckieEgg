#include "header.h"

//Exit using window close
bool exit_bool = false;
void close_button_handler(){
	exit_bool = TRUE;
}
END_OF_FUNCTION(close_button_handler)

//Main function
int main(){
	//Allegro init
	allegro_init();
	set_color_depth(32); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1280, 960, 0, 0);
	set_window_title("Chuckie Egg");
	srand(time(NULL));

	//Installations
	install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,0);
	install_timer();
	install_keyboard();
	install_mouse();

	//Close button
    LOCK_FUNCTION(close_button_handler);
    set_close_button_callback(close_button_handler);

	//Show menu
	ce_menu *menu = new ce_menu();
	menu->setupMenu();
	menu->showMenu();
	delete menu;

	allegro_exit();

	return 1;
}

END_OF_MAIN();