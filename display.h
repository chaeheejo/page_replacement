//
//  display.h
//  page_replacement
//
//  Created by chaehee on 2022/11/15.
//

#ifndef display_h
#define display_h
 
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "FIFO.h"
#include "LIFO.h"
#include "LRU.h"
#include "LFU.h"

void user_menu(void);
int* get_random_input(void);
int* get_file_input(void);

#endif /* display_h */
