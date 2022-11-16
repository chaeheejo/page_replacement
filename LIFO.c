//
//  LIFO.c
//  Last In First Out
//  page_replacement
//
//  Created by chaehee on 2022/11/15.
//

#include "LIFO.h"

extern int STREAM_SIZE;
extern int FRAME_SIZE;

void LIFO(int* ref){
    printf("\n\n==LIFO simulation start==\n\n");
    int page_fault=0;
    
    int* frame = (int*) calloc(FRAME_SIZE, sizeof(int));
    
    int frame_size=0,flag=0;
    for(int i=0;i<STREAM_SIZE;i++){
        flag=0;
        
        if(is_exist(frame, ref[i])==NOTFOUND){
            frame[frame_size]=ref[i];
            
            if(frame_size<FRAME_SIZE-1){
                frame_size++;
            }
            
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
    
    free(frame);
    
    printf("\nTotal number of page fault %d\n", page_fault);
    printf("==LIFO simulation end==\n\n");
}
