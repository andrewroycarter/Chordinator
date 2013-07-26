//
//  BufferScanner.c
//  test
//
//  Created by Andrew Carter on 7/26/13.
//  Copyright (c) 2013 PinchStudios. All rights reserved.
//

#include "buffer_scanner.h"
#include <stdio.h>
#include <string.h>

void buffer_scanner_init(BufferScanner *buffer_scanner, char *buffer, int length, char delimiter) {
   
    buffer_scanner->buffer = buffer;
    buffer_scanner->delimiter = delimiter;
    buffer_scanner->length = length;
    buffer_scanner->position = 0;
    
}

void buffer_scanner_scan_next_string(BufferScanner *buffer_scanner, char *string, int max_string_size) {
    
    memset(string, '\0', max_string_size);
    
    int string_position = 0;
    int finished = 0;
    char delimiter = buffer_scanner->delimiter;
    char *buffer = buffer_scanner->buffer;
    
    while (!finished &&
            buffer_scanner->position < buffer_scanner->length &&
            string_position < max_string_size) {
        
        char current_char = buffer[buffer_scanner->position];
        if (current_char != delimiter)
        {
            memcpy(string + string_position, buffer + buffer_scanner->position, 1);
        }
        else
        {
            finished = 1;
        }
        buffer_scanner->position++;
        string_position++;
    }
    
}
