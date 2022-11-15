//
//  LFU.c
//  page_replacement
//
//  Created by chaehee on 2022/11/15.
//

#include "LFU.h"

extern int STREAM_SIZE;
extern int FRAME_SIZE;

void LFU(int* ref){
    printf("\n\n==LFU simulation start==\n\n");
    int page_fault=0;
    
    int* frame = (int*) calloc(FRAME_SIZE, sizeof(int));
    int* time = (int*) calloc(31, sizeof(int));
    int* count = (int*) calloc(31, sizeof(int));
    
    int min_time=0, oldest=0;
    int frame_size=0, flag=0;
    
    for(int i=0;i<STREAM_SIZE;i++){
        count[ref[i]]++;
        time[ref[i]]=i;
        flag=0;
        
        oldest = frame[0];
        for(int j=0;j<FRAME_SIZE;j++){
            if(count[oldest]>count[frame[j]]){
                oldest=frame[j];
            }
        }
        
        if(is_exist(frame, ref[i])==NOTFOUND){
            if(frame_size<FRAME_SIZE){
                frame[frame_size] = ref[i];
                page_fault++;
                frame_size++;
                flag=1;
            }
            else{
                min_time = STREAM_SIZE;
                int tmp=0;
                
                for(int j=0;j<FRAME_SIZE;j++){  
                    if(count[frame[j]]==count[oldest] && time[frame[j]]<min_time){
                        tmp = j;
                        min_time = time[frame[j]];
                    }
                }
                count[frame[tmp]] = 0;
                frame[tmp] = ref[i];
                page_fault++;
                flag=1;
            }
        }
        
        printf("#%-5d page : %-3d   frame :", i+1, ref[i]);
        print_frame(frame);
        
        if(flag)
            printf("%5c\n", 'F');
        else
            printf("%5c\n", ' ');
        
    }
    
    printf("\nTotal number of page fault %d\n", page_fault);
    printf("==LFU simulation end==\n\n");
    free(frame);
    free(time);
    free(count);
}
