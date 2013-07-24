#include "chord_type_menu.h"

#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

static Window chord_type_window;

void setup_chord_type_window();
void chord_type_window_load(Window *window);

void chord_type_window_load(Window *window) {


}

void display_chord_type_menu(char *root_note) {
    
    setup_chord_type_window();

}


void setup_chord_type_window() {

  window_init(&chord_type_window, "Chordinator");
  window_set_window_handlers(&chord_type_window, (WindowHandlers){
            .load = chord_type_window_load
          });
  window_stack_push(&chord_type_window, true /* Animated */);

}
