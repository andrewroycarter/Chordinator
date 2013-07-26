#include "chord.h"

#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "buffer_scanner.h"

static Window chord_window;
static char chord_fingering[6];
static TextLayer text_layer;

void setup_chord_window();
void chord_window_load(Window *window);
void get_chord_fingering(const char *chord);

void chord_window_load(Window *window) {

  Layer *root_layer = window_get_root_layer(window);

  text_layer_init(&text_layer, GRect(0, 50, 200, 45));  
  text_layer_set_text_alignment(&text_layer, GTextAlignmentCenter);
  text_layer_set_font(&text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text(&text_layer, chord_fingering);
  layer_add_child(root_layer, (Layer *)&text_layer);

}

void display_chord(const char *chord) {

    get_chord_fingering(chord);
    setup_chord_window();
    window_stack_push(&chord_window, true /* Animated */);

}

void get_chord_fingering(const char *chord) {

    ResHandle res = resource_get_handle(RESOURCE_ID_CHORDS);
    uint8_t buffer[256];
    resource_load(res, buffer, 256);

    BufferScanner buffer_scanner;
    buffer_scanner_init(&buffer_scanner, (char *)buffer, resource_size(res), ',');

    char string[16];
    int match_found = 0;

    int safe = 0;

    while (!match_found && buffer_scanner.position < (int)resource_size(res)) {

        buffer_scanner_scan_next_string(&buffer_scanner, string, 16);     
        if (strncmp(string, chord, 5) == 0) {
                buffer_scanner_scan_next_string(&buffer_scanner, chord_fingering, 6);
                match_found = 1;
        }
        safe++;
        if (safe > 10) {
            break;
        }
    }
}

void setup_chord_window() {

    window_init(&chord_window, "Chordinator");
    window_set_window_handlers(&chord_window, (WindowHandlers){
            .load = chord_window_load
    });

}
