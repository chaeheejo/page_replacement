//
//  tools.h
//  page_replacement
//
//  Created by chaehee on 2022/11/15.
//

#ifndef tools_h
#define tools_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int lowest_priority(int** frame, int cur);
int how_far(int* ref, int pos, int page_num);

int is_exist(int* frame, int page_num);
void print_frame(int* frame);
int is_exist_dimension(int** frame, int page_num);
void print_frame_dimension(int** frame);

int* get_random_input(int esc_flag);
int* get_file_input(int esc_flag);
int* convert_esc_to_normal(int* esc_ref);

#define NOTFOUND -1

#endif /* print_form_h */
