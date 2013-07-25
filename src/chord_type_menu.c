#include "chord_type_menu.h"

#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

static Window chord_type_window;
static SimpleMenuLayer chord_type_menu_layer;
static SimpleMenuSection chord_type_menu_sections[1];
static SimpleMenuItem chord_type_menu_items[3];
static char *types[3] = {"Major", "Minor", "7"};
static char menu_item_names[64];
static char *root_note;

void setup_chord_type_window();
void chord_type_window_load(Window *window);
void setup_chord_type_menu_sections();

void setup_chord_type_menu_sections() {
    
    int offset = 0;

    for (int i = 0; i < (int)(sizeof(types) / sizeof(types[0])); i++) {
       
        char title[16];
        snprintf(title, sizeof(title), "%s %s", root_note, types[i]);  
        memcpy(menu_item_names + offset, title, sizeof(title));
        char *name = menu_item_names + offset;
        
        offset += sizeof(title) / sizeof(title[0]);

        chord_type_menu_items[i] = (SimpleMenuItem) {
           .title = name,
           .callback = NULL,
        };

   }

   chord_type_menu_sections[0] = (SimpleMenuSection) {
        .title = "Select Type",
        .items = chord_type_menu_items,
        .num_items = sizeof(chord_type_menu_items) / sizeof(chord_type_menu_items[0])
    };

}

void chord_type_window_load(Window *window) {

    Layer *root_layer = window_get_root_layer(&chord_type_window);

    simple_menu_layer_init(
                &chord_type_menu_layer,
                layer_get_bounds(root_layer), 
                &chord_type_window,
                chord_type_menu_sections,
                1,
                NULL
            );

    layer_add_child(root_layer, &chord_type_menu_layer.menu.scroll_layer.layer);

}

void display_chord_type_menu(char *root_note_) {
    
    root_note = root_note_;
    setup_chord_type_window();
    setup_chord_type_menu_sections();
    window_stack_push(&chord_type_window, true /* Animated */);

}


void setup_chord_type_window() {

  window_init(&chord_type_window, "Chordinator");
  window_set_window_handlers(&chord_type_window, (WindowHandlers) {
            .load = chord_type_window_load
          });

}
