#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "chord_type_menu.h"

#define MY_UUID { 0x63, 0xB8, 0x75, 0x5C, 0x3E, 0x16, 0x45, 0xF6, 0xB4, 0x63, 0x5E, 0x0B, 0x68, 0xAE, 0x56, 0x1A }
PBL_APP_INFO(MY_UUID,
             "Chordinator", "Pinch Studios",
             0, 1, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

// Used to build the menu and build the key used to find the fingering
// in /resources/src/raw/chords
static char *notes[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

static Window chord_menu_window;
static SimpleMenuLayer root_note_menu_layer;
static SimpleMenuSection root_note_menu_sections[1];
static SimpleMenuItem root_note_menu_items[12];

void setup_chord_menu_window();
void setup_menu_sections();

void handle_init(AppContextRef ctx)
{
    resource_init_current_app(&VERSION); 
    setup_chord_menu_window();
}

void pbl_main(void *params)
{
  PebbleAppHandlers handlers =
  {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
}

void note_menu_item_selected_callback(int index, void *context)
{
    display_chord_type_menu(notes[index]);
}

void setup_menu_sections()
{
    for (int i = 0; i < 12; i++)
    {
        root_note_menu_items[i] = (SimpleMenuItem)
        {
            .title = notes[i],
            .callback = note_menu_item_selected_callback,
        };
    }

    root_note_menu_sections[0] = (SimpleMenuSection)
    {
        .title = "Select Root Note",
        .items = root_note_menu_items,
        .num_items = sizeof(root_note_menu_items) / sizeof(root_note_menu_items[0])
    };
}

void chord_menu_window_load(Window *window)
{
    Layer *root_layer = window_get_root_layer(&chord_menu_window);

    simple_menu_layer_init(
                &root_note_menu_layer,
                layer_get_bounds(root_layer), 
                &chord_menu_window,
                root_note_menu_sections,
                1,
                NULL
            );

    layer_add_child(root_layer, &root_note_menu_layer.menu.scroll_layer.layer);
}

void setup_chord_menu_window()
{
    setup_menu_sections();

    window_init(&chord_menu_window, "Chordinator");
    window_set_window_handlers(&chord_menu_window, (WindowHandlers)
            {
            .load = chord_menu_window_load
            });

  window_stack_push(&chord_menu_window, true);
}
