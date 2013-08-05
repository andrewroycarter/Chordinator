//
//  BufferScanner.h
//  test
//
//  Created by Andrew Carter on 7/26/13.
//  Copyright (c) 2013 PinchStudios. All rights reserved.
//

#ifndef test_BufferScanner_h
#define test_BufferScanner_h

typedef struct {
    char delimiter; // char that seperates the string. ',' in "one,two,three"
    char *buffer; // string to scan
    int length; // length of string to scan
    int position; // current position to scan from (starts at 0)
} BufferScanner;

// sets up buffer scanner
void buffer_scanner_init(BufferScanner *buffer_scanner, char *buffer, int length, char delimiter);

// scans to next instance of delimiter, and writes the string scanned into string variable
void buffer_scanner_scan_next_string(BufferScanner *buffer_scanner, char *string, int max_string_size);

#endif
