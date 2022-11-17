//
//  FIFO.c
//  First In First Out
//  page_replacement
//
//  Created by chaehee on 2022/11/15.
//

#include "FIFO.h"

extern int REF_SIZE;
extern int FRAME_SIZE;

void FIFO(int* ref, int output_flag, FILE* fp){
    printf("\n\n==FIFO simulation start==\n\n");
    
    if(output_flag)
        fprintf(fp, "\n\n==FIFO simulation start==\n\n");
    
    int page_fault=0;
    
    int* frame = (int*) calloc(FRAME_SIZE, sizeof(int));
    
    int cur=0,flag=0;
    for(int i=0;i<REF_SIZE;i++){
        flag=0;
        
        if(is_exist(frame, ref[i])==NOTFOUND){
            frame[cur]=ref[i];
            cur = (cur+1)%FRAME_SIZE;
            page_fault++;
            flag=1;
        }
        
        printf("#%-5d page : %-3d   frame :", i+1, ref[i]);
        
        if(output_flag)
            fprintf(fp, "#%-5d page : %-3d   frame :", i+1, ref[i]);
        
        print_frame(frame, fp, output_flag);
        
        if(flag){
            printf("%5c\n", 'F');
            
            if(output_flag)
                fprintf(fp, "%5c\n", 'F');
        }
        else{
            printf("%5c\n", ' ');
            
            if(output_flag)
                fprintf(fp, "%5c\n", ' ');
        }
    }
    
    free(frame);
    
    printf("\nTotal number of page fault %d\n", page_fault);
    printf("==FIFO simulation end==\n\n\n");
    
    if(output_flag){
        fprintf(fp, "\nTotal number of page fault %d\n", page_fault);
        fprintf(fp, "==FIFO simulation end==\n\n\n");
    }
}
