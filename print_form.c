//
//  print_form.c
//  page_replacement
//
//  Created by chaehee on 2022/11/15.
//

#include "print_form.h"

int STREAM_SIZE=0;
int FRAME_SIZE=0;

int how_far(int* ref, int pos, int page_num){
    int dist=0;
    for(int i=pos+1;i<STREAM_SIZE;i++){
        if(ref[i]!=page_num)
            dist++;
        else
            break;
    }
    
    return ++dist;
}

int is_exist(int* frame, int page_num){
    for(int i=0;i<FRAME_SIZE;i++){
        if(frame[i]==page_num)
            return i;
    }
    return NOTFOUND;
}

void print_frame(int* frame){
    for(int i=0;i<FRAME_SIZE;i++)
        printf("%5d", frame[i]);
}
