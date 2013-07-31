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

void buffer_scanner_init(BufferScanner *buffer_scanner, char *buffer, int length, char delimiter)
{   
    buffer_scanner->buffer = buffer;
    buffer_scanner->delimiter = delimiter;
    buffer_scanner->length = length;
    buffer_scanner->position = 0;    
}

void buffer_scanner_scan_next_string(BufferScanner *buffer_scanner, char *string, int max_string_size)
{  
    // null out passed in string
    memset(string, '\0', max_string_size);
    
    int string_position = 0;
    char delimiter = buffer_scanner->delimiter;
    char *buffer = buffer_scanner->buffer;
    
    while (buffer_scanner->position < buffer_scanner->length && /* make sure we don't scan past buffer */
           string_position < max_string_size /* make sure we don't overflow passed in string */)
    {   
        // capture current char
        char current_char = buffer[buffer_scanner->position];
        
        // move positions up one in our buffer position and string position for next pass
        buffer_scanner->position++;
        string_position++;
        
        // if we haven't hit the delimiter yet, copy the char into our string
        if (current_char != delimiter)
        {
            memcpy(string + string_position, buffer + buffer_scanner->position, 1);
        }
        else
        {
            // we hit the delimiter- string should now contain the next item
            break;
        }
    }
}
