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
    char delimiter;
    char *buffer;
    int length;
    int position;
} BufferScanner;

void buffer_scanner_init(BufferScanner *buffer_scanner, char *buffer, int length, char delimiter);
void buffer_scanner_scan_next_string(BufferScanner *buffer_scanner, char *string, int max_string_size);

#endif
