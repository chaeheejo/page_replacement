//
//  LRU.c
//  Least Recently Used
//  page_replacement
//
//  Created by chaehee on 2022/11/15.
//

#include "LRU.h"

extern int STREAM_SIZE;
extern int FRAME_SIZE;

void LRU(int* ref){
    printf("\n\n==LRU simulation start==\n\n");
    int page_fault=0;
    
    int* frame = (int*) calloc(FRAME_SIZE, sizeof(int));
    
    int flag=0, cur=0, frame_size=0;
    for(int i=0;i<STREAM_SIZE;i++){
        flag=0;
        
        if((cur = is_exist(frame, ref[i]))==NOTFOUND){
            if(frame_size<FRAME_SIZE){
                frame[frame_size] = ref[i];
                frame_size++;
            }
            else{
                for(int j=1;j<FRAME_SIZE;j++){
                    frame[j-1] = frame[j];
                }
                
                frame[FRAME_SIZE-1] = ref[i];
            }
            
            page_fault++;
            flag=1;
        }
        else{
            int tmp = frame[cur];
            for(int j=cur;j<frame_size-1;j++){
                frame[j] = frame[j+1];
            }
            
            frame[frame_size-1] = tmp;
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
    printf("==LRU simulation end==\n\n");
}
