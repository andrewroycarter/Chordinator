#include "chord_type_menu.h"
#include "chord.h"

#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

static Window chord_type_window;
static SimpleMenuLayer chord_type_menu_layer;
static SimpleMenuSection chord_type_menu_sections[1];
static SimpleMenuItem chord_type_menu_items[3];

// Holds titles built for use in menu items. Because there is no
// dynamic memory allocation, we have to get this space now
static char menu_item_names[128];

// Holds root note passed in from note selection screen
static char *root_note;

// Types of supported chords. Used to build menu titles
static char *types[3] = {"Major", "Minor", "Major 7"};

// function prototypes
void setup_chord_type_window();
void chord_type_window_load(Window *window);
void setup_chord_type_menu_sections();
void chord_type_menu_item_selected_callback(int index, void *context);

// sets up items and sections for our menu
void setup_chord_type_menu_sections()
{   
    int offset = 0;
   
    // builds title strings and creates items with them. We store
    // the built title strings in menu_item_names. remember, no dynamic mem allocation! 
    for (int i = 0; i < (int)(sizeof(types) / sizeof(types[0])); i++)
    {   
        char title[16];
        snprintf(title, sizeof(title), "%s %s", root_note, types[i]);  
        memcpy(menu_item_names + offset, title, sizeof(title));
        char *name = menu_item_names + offset;
        
        offset += sizeof(title) / sizeof(title[0]);

        chord_type_menu_items[i] = (SimpleMenuItem)
        {
           .title = name,
           .callback = chord_type_menu_item_selected_callback,
        };
   }

   // make our section with the items generated above
   chord_type_menu_sections[0] = (SimpleMenuSection)
   {
        .title = "Select Type",
        .items = chord_type_menu_items,
        .num_items = sizeof(chord_type_menu_items) / sizeof(chord_type_menu_items[0])
    };
}

// callback for when a menu item is selected. Display chord window
void chord_type_menu_item_selected_callback(int index, void *context)
{
    // Pass in menu item title which will be used for chord lookup in
    // resources/src/raw/chords
    display_chord(chord_type_menu_items[index].title);
}

// setup our menu layer when the window loads
void chord_type_window_load(Window *window)
{
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

// configures window and menu sections, and pushes it to the window stack
void display_chord_type_menu(char *root_note_)
{
    root_note = root_note_;
    setup_chord_type_window();
    setup_chord_type_menu_sections();
    window_stack_push(&chord_type_window, true /* Animated */);
}

// setup window and it's handlers
void setup_chord_type_window()
{
  window_init(&chord_type_window, "Chordinator");
  window_set_window_handlers(&chord_type_window, (WindowHandlers) {
            .load = chord_type_window_load
          });
}
