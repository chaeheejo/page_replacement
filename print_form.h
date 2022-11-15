//
//  print_form.h
//  page_replacement
//
//  Created by chaehee on 2022/11/15.
//

#ifndef print_form_h
#define print_form_h

#include <stdio.h>
#include <stdlib.h>  

int how_far(int* ref, int pos, int page_num);
int is_exist(int* frame, int page_num);
void print_frame(int* frame);

#define NOTFOUND -1

#endif /* print_form_h */
