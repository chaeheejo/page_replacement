//
//  FIFO.c
//  page_replacement
//
//  Created by chaehee on 2022/11/15.
//

#include "FIFO.h"

extern int STREAM_SIZE;
extern int FRAME_SIZE;

void FIFO(int* ref){
    printf("\n\n==FIFO simulation start==\n\n");
    int page_fault=0;
    
    int* frame = (int*) calloc(FRAME_SIZE, sizeof(int));
    
    int cur=0,flag=0;
    for(int i=0;i<STREAM_SIZE;i++){
        flag=0;
        
        if(is_exist(frame, ref[i])==NOTFOUND){
            frame[cur]=ref[i];
            cur = (cur+1)%FRAME_SIZE;
            page_fault++;
            flag=1;
        }
        
        printf("#%-5d page : %-3d   frame :", i+1, ref[i]);
        print_frame(frame);
        
        if(flag)
            printf("%5c\n", 'F');
        else
            printf("%5c\n", ' ');
    }
    
    printf("\nTotal number of page fault %d\n", page_fault);
    printf("==FIFO simulation end==\n\n");
    free(frame);
}
